#include <thread>

#include "Engine.h"
#include "OpenCVHelper.h"
#include "Histogram.h"
#include "BHistogram.h"
#include "ImageMetricsHelper.h"


using namespace cv;

namespace im
{
	Engine::Engine(void) //: _nthreads(std::thread::hardware_concurrency())
	{
	}


	Engine::~Engine(void)
	{
	}

	template<class ForwardIt> ForwardIt max_element(ForwardIt first, ForwardIt last)
	{
		if (first == last) {
			return last;
		}
		ForwardIt largest = first;
		++first;
		for (; first != last; ++first) {
			if (*largest < *first) {
				largest = first;
			}
		}
		return largest;
	}

	Error Engine::CalculateImageMetric(const WChar* imagePath, WorkProgressInteropNegotiator& negotiator, ImageInfo * exportImageInfo)
	{
		//ImageInfo imageInfo;
		Mat img;
		wstring path = StringHelper::ToWstring(imagePath);
		if (!OpenCVHelper::ReadImage(img, path, negotiator))
			Error::NOT_READ_IMAGE;

		wcscpy_s(exportImageInfo->Path, imagePath);
		exportImageInfo->JpegPeak = ImageMetricsHelper::CalcDoubleJpegCompressionPeaks(img);
		exportImageInfo->JpegQuality = 0;
		exportImageInfo->Sharpness = 0;
		exportImageInfo->Height = 0;
		exportImageInfo->Width = 0;

		return Error::OK;
	}

	ImageInfo Engine::ResizeAndCalculateImageMetric(const WChar* image, int width, int heigth)
	{
		return ImageInfo();
	}

	Error Engine::CalculateMultiImageMetric(ImageInfo* pPointArray, int size, WorkProgressInteropNegotiator& negotiator )
	{
		 //ImageInfo* pCur = pPointArray;
		// unsigned int j = 1;

		//for ( int i = 0; i < size; i++ )
		//{
		//	pCur->JpegPeak = j;
		//	j++;
		//	pCur++;
		//}

		 size_t nthreads = std::thread::hardware_concurrency();
		 std::vector<std::thread> threads(nthreads);
		std::mutex mutex;
		std::unique_lock<std::mutex> guard(mutex);
		guard.unlock();

		const size_t step = size / nthreads;
		for(unsigned char t = 0; t < nthreads; t++)
		{
			const size_t beginIndex = t * step;
			size_t endIndex = size;
			if (t+1 == nthreads)
				endIndex = size;
			else
				endIndex = beginIndex + step;

			threads[t] = std::thread(std::bind(
				[&](const size_t & beginIndex,
					const size_t & endIndex,
					const int t)
			{
				for (size_t i = beginIndex; i < endIndex; i++)
				{
					//if (negotiator.cancellationPending()) {
					//	negotiator.cancel = true; 
					//	negotiator.addToLogCallback((L"ComputeHashes thread " + to_wstring(t) + L" stopped").c_str());
					//	break;
					//}

					Mat img;
					wstring path = StringHelper::ToWstring(pPointArray[i].Path);
					if (!OpenCVHelper::ReadImage(img, path, negotiator))
						Error::NOT_READ_IMAGE;
					pPointArray[i].JpegPeak = ImageMetricsHelper::CalcDoubleJpegCompressionPeaks(img);

					//guard.lock();
					//negotiator.progressCallback(progress, size, (*file).c_str());
					//progress++;
					//guard.unlock();

				}//end for(auto file = iterator; file != end; ++file) 
			}, beginIndex, endIndex, t));
		};

		std::for_each(threads.begin(), threads.end(), [](std::thread& x){x.join();});

		return Error::OK;
	}
}
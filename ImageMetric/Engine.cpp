#include "Engine.h"
#include "OpenCVHelper.h"
#include "Histogram.h"
#include "BHistogram.h"
#include "ImageMetricsHelper.h"



using namespace cv;

namespace im
{
	Engine::Engine(void)
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
}
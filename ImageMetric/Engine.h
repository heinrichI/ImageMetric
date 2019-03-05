#pragma once

#include "ImageMetric.h"


#include <string>
#include <vector>
#include <set>
#include <map>
//#include <thread>
#include <mutex>


using namespace std;

namespace im
{

	class Engine
	{
	private:
		//const size_t _nthreads;
	public:
		Engine(void);
		~Engine(void);

		//Error Initialize(void);
		//Error Release(void);

		static Error CalculateImageMetric(const WChar* imagePath, WorkProgressInteropNegotiator& negotiator, ImageInfo * exportImageInfo);
		static ImageInfo ResizeAndCalculateImageMetric(const WChar* image, int width, int heigth);
		static Error CalculateMultiImageMetric(ImageInfo* pPointArray, int size, WorkProgressInteropNegotiator& negotiator );
	};

}

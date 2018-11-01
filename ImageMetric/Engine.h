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
	public:
		Engine(void);
		~Engine(void);

		//Error Initialize(void);
		//Error Release(void);

		static ImageInfo CalculateImageMetric(const WChar* image);
		static ImageInfo ResizeAndCalculateImageMetric(const WChar* image, int width, int heigth);
	};

}

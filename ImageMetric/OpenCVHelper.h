#pragma once

#include "StringHelper.h"
#include "PathHelper.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifdef _DEBUG
#pragma comment (lib, "opencv_core2413d.lib")
#pragma comment (lib, "opencv_highgui2413d.lib")
#pragma comment (lib, "libtiffd.lib")
#pragma comment (lib, "libjpegd.lib")
#pragma comment (lib, "libpngd.lib")
#pragma comment (lib, "libjasperd.lib")
#pragma comment (lib, "IlmImfd.lib")
#pragma comment (lib, "zlibd.lib")
#pragma comment (lib, "opencv_imgproc2413d.lib")
#else
#pragma comment (lib, "opencv_core2413.lib")
#pragma comment (lib, "opencv_highgui2413.lib")
#endif


using namespace cv;

namespace im
{
	class OpenCVHelper
	{
	public:

		static bool ReadImage(Mat & img, const wstring & sourcePath, WorkProgressInteropNegotiator& negotiator)
		{
			if (!img.empty())
				return true;

			wstring path = PathHelper::GetPathForSearchInAPI(sourcePath);
			img = imread(StringHelper::ToString(path));
			if( img.empty())
			{
				wstring mes = L"Can not read image " + sourcePath;
				negotiator.addToLogCallback(mes.c_str());
				return false;
			}
			if ( img.cols < 4 || img.rows < 4)
			{
				negotiator.addToLogCallback((L"Image width or height < 4 for file " + sourcePath).c_str());
				return false;
			}

			return true;
		}


		
	};
}


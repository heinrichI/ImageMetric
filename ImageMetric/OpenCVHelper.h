#pragma once

#include "StringHelper.h"
#include "PathHelper.h"

//using namespace cv;

namespace im
{
	class OpenCVHelper
	{
	public:

		/*static bool ReadImage(Mat & img, const wstring & sourcePath, WorkProgressInteropNegotiator& negotiator)
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

		static double GetArea(const vector<Point2f> & obj, const vector<Point2f> & scene, const SurfInfo & objInfo)
		{
			if (obj.size()>3)
			{
				Mat H = findHomography( obj, scene, CV_RANSAC );

				//-- Get the corners from the image_1 ( the object to be "detected" )
				std::vector<Point2f> obj_corners(4);
				obj_corners[0] = Point(0,0); 
				obj_corners[1] = Point( objInfo.width, 0 );
				obj_corners[2] = Point( objInfo.width, objInfo.heigth ); 
				obj_corners[3] = Point( 0, objInfo.heigth );
				std::vector<Point2f> scene_corners(4);

				perspectiveTransform( obj_corners, scene_corners, H);

				return contourArea(scene_corners);
			}

			return 0.0;
		}

		static SurfInfo GetSurfInfo(const wstring & path)
		{
			const int minHessian = 400;
			string convPath = StringHelper::ToString(path);
			Mat img = imread(convPath, CV_LOAD_IMAGE_GRAYSCALE);
			if(!img.empty())
			{
				SurfInfo si;
				si.width = img.cols;
				si.heigth = img.rows;
				// detecting keypoints
				SurfFeatureDetector detector(minHessian);
				//vector<KeyPoint> keypoints;
				detector.detect(img, si.keypoints);

				// computing descriptors
				SurfDescriptorExtractor extractor;
				//Mat descriptors;
				extractor.compute( img, si.keypoints, si.descriptors );
				return si;
			}

			throw std::runtime_error("Cannot read image " + convPath);
		}*/
	};
}


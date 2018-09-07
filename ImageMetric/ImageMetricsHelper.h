#pragma once

#include <math.h>
#include <stdio.h>
#include <cmath>
#include <float.h>
//#include <math.h>
#include <string>
#include <vector>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std; 

namespace im
{
	//isnan поддерживаетя с Visual Studio 2013
	//#define VALIDATE(x) ( std::isnan(x) ) ? 0 : x
	#define isnan(x) _isnan(x)
	#define VALIDATE(x) ( isnan(x) ) ? 0 : x

	#ifndef sign
	#define sign(x,y) ((y) < 0 ? ((x) < 0 ? (x) : -(x)) : ((x) < 0 ? -(x) : (x)))
	#endif

	class ImageMetricsHelper
	{
	public:

		ImageMetricsHelper(void)
		{
		}

		~ImageMetricsHelper(void)
		{
		}

		/*------------------------------------------------------------------------
		JPEG quality is measured using the no-reference quality estimation of
		Z. Wang, H. R. Sheikh, and A. C. Bovik. No-reference perceptual quality
		assessment of jpeg compressed images. In ICIP, 2002.
		------------------------------------------------------------------------*/
		static inline double CalcJpegQuality( const Mat& gray_img )
		/*-----------------------------------------------------------------------*/
		{
			// Convert to grayscale image with 64bit doubles
			cv::Mat img;
			gray_img.convertTo( img, CV_64FC1 );
    
			const int height = img.rows;
			const int width = img.cols;
    
			if (height<16 || width<16)
			{
				return -2.0;
			}
    
			// feature extraction: horizontal features
			Mat dh, dh1, dh2;
			dh1 = img( Rect(1, 0, width-1, height) );
			dh2 = img( Rect(0, 0, width-1, height) );
			dh = dh1 - dh2;
    

			double sum = 0;
			int count = 0;
			double sumz = 0;
			for (int y=0; y < height; ++y) 
			{
				for (int x=0; x < width-2; ++x) 
				{
					if ((x+1)%8==0 && x>0 && (x+1)<8*floor(width/8))
					{
						sum += std::abs( dh.at<double>(y,x) );
						count++;
					}
					try
					{
					//double signval = copysign( 1.0, dh.at<double>(i,j) ) *
					//copysign( 1.0, dh.at<double>(i,j+1) );
					//double d = dh.at<double>(0,0);
					double signval = sign( 1.0, dh.at<double>(y,x) ) * sign( 1.0, dh.at<double>(y,x+1) );
					if (signval < 0)
						sumz += 1;
					}
					catch (cv::Exception& e) 
					{
						cerr << "Error: " << e.msg << endl;
						// nothing more we can do
						exit(1);
					}
				}
			}
    
			double bh = sum / count;
			//cv::abs - Computes per-element absolute values of the input array.
			//mean - Calculates an average (mean) of array elements.
			double ah = (8.0 * mean( cv::abs(dh) )[0] - bh) / 7;
			double zh = sumz / (height * (width-2));
    
			// feature extraction: vertical features
			Mat dv1, dv2, dv;
			dv1 = img( Rect(0, 1, width, height-1) );
			dv2 = img( Rect(0, 0, width, height-1) );
			dv = dv1 - dv2;
    
			sum = 0;
			count = 0;
			sumz = 0;

			for (int i=0; i < height-2; ++i) 
			{
				for (int j=0; j < width - 1; ++j)
				{
					if ((i+1)%8==0 && i>0 && (i+1)<8*floor(height/8))
					{
						sum += std::abs( dv.at<double>(i,j) );
						count++;
					}
					try
					{
					//double signval = std::copysign( 1.0, dv.at<double>(i,j) ) *	copysign( 1.0, dv.at<double>(i,j+1) );
					double signval = sign( 1.0, dv.at<double>(i,j) ) *	sign( 1.0, dv.at<double>(i,j+1) );
					if (signval < 0)
						sumz += 1;
					}
					catch (cv::Exception& e) 
					{
						cerr << "Error: " << e.msg << endl;
						double t1 = dv.at<double>(i,j-1);
						double t2 = dv.at<double>(i,j);
						double t3 = dv.at<double>(i,j+1);
						// nothing more we can do
						exit(1);
					}
				}
			}


    
			double bv = sum / count;
			double av = (8.0 * mean( cv::abs(dv) )[0] - bv) / 7;
			double zv = sumz / (width * (height-2));
    
			//combined features
			double B = (bh + bv) / 2;
			double A = (ah + av) / 2;
			double Z = (zh + zv) / 2;
    
			// Quality Prediction
			const double alpha = -245.8909;
			const double beta = 261.9373;
			const double gamma1 = -239.8886;
			const double gamma2 = 160.1664;
			const double gamma3 = 64.2859;
    
			double score = alpha + beta *
			std::pow( B, (gamma1/10000) ) *
			std::pow( A, (gamma2/10000) ) *
			std::pow( Z, (gamma3/10000) );
    
			return VALIDATE(score);
		}

		/*------------------------------------------------------------------------
		Sharpness is measured as the sum of magnitude in frequency domain
		------------------------------------------------------------------------*/
		static inline double CalcSharpness( const Mat& gray_img )
		/*-----------------------------------------------------------------------*/
		{
			Mat img;
			gray_img.convertTo( img, CV_32FC1 );
			img *= 1./255;
    
			Mat dx, dy;
			Sobel( img, dx, img.type(), 1, 0, 3 );
			Sobel( img, dy, img.type(), 0, 1, 3 );
			magnitude( dx, dy, dx );
    
			int npixels = gray_img.rows * gray_img.cols;
			return VALIDATE(cv::sum(dx)[0] / npixels);
		} 
	};
}


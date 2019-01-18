#include "Engine.h"
#include "OpenCVHelper.h"

#include <iostream>
#include <iomanip>

using namespace cv;

namespace im
{
	Engine::Engine(void)
	{
	}


	Engine::~Engine(void)
	{
	}

	ImageInfo Engine::CalculateImageMetric(const WChar* image, WorkProgressInteropNegotiator& negotiator)
	{
		Mat img;
		wstring path = StringHelper::ToWstring(image);
		if (!OpenCVHelper::ReadImage(img, path, negotiator))
			return ImageInfo();

		//Mat dctOut;
		//Mat imgFloat = Mat( img.rows, img.cols, CV_64F);
		//img.convertTo(imgFloat, CV_64F);
		//dct(imgFloat, dctOut);

		int dct_rows;
		int dct_cols;
		if (img.rows %8 != 0) 
			dct_rows = img.rows + 8 - img.rows % 8;
		else
			dct_rows = img.rows;

		if (img.cols %8 != 0) 
			dct_cols = img.cols + 8 - img.cols % 8;
		else
			dct_cols = img.cols;

		//vector<Mat> bgr_planes;
		//split( img, bgr_planes );

		Mat img2;
		img2.create(dct_rows, dct_cols, CV_8U);
		img.convertTo(img2, CV_8U); // or CV_32F works (too)

		Mat BGR2YCrCb_image;
		//BGR2YCrCb_image.create(dct_rows, dct_cols, CV_8U);
		cvtColor(img2, BGR2YCrCb_image, COLOR_BGR2YCrCb);

		vector<Mat> bgr_planes;
		split( BGR2YCrCb_image, bgr_planes );
		//cv::Mat Y = BGR2YCrCb_image.colRange(0, 1);
		//cv::Mat Y = BGR2YCrCb_image.rowRange(0, 1);
		//Mat Dst (BGR2YCrCb_image, Rect(0, 0, 1, dct_rows) );
		//Mat Y = Dst.clone();
		//Mat tmp;
		//tmp.create(dct_rows, dct_cols, CV_8U);
		//BGR2YCrCb_image.convertTo(tmp, CV_8U); 
		//cv::Mat Y = tmp.colRange(0, 1);
		//Mat Y = BGR2YCrCb_image.col(0);
		Mat y_ = bgr_planes[0];

		//cout << y_.type() << endl;

		//for (int i = 0; i < y_.size().height; i++)
		//{
		//	cout << "i=" << i << " ";
		//	for (int j = 0; j < y_.size().width; j++)
		//	{
		//		cout <<  (float)y_.at<uchar>(i,j) << ",";
		//	}
		//	cout << endl;
		//}

		 int w = y_.cols;
		 int h = y_.rows;
		 double n = w*h/64;

		 //разбиваем на квадратики 8x8
		 //int sz[] = {h / 8, 8, w / 8, 8};
		//	Mat map(4, sz, CV_8U);

		 //Mat Y = y.reshape(120,8);


			 // Cloning the image to another for visualization later, if you do not want to visualize the result just comment every line related to visualization 
            //cv::Mat maskImg = y.clone();
            // Checking if the clone image was cloned correctly 
            //if(!maskImg.data || maskImg.empty())
             //   std::cerr << "Problem Loading Image" << std::endl;

			std::vector<cv::Mat> blocks;
			int colDivisor = w / 8;
			int rowDivisor = h / 8;

			
			//int dims[] = {colDivisor,rowDivisor,8,8};
			//cv::Mat y2(4, dims, CV_32F);
			 // return matrix with the shuffled dimensions
  //  return mat1.reshape(mat2.channels(), mat2.dims, mat2.size.p);
		// Mat y2 = y_.reshape(1,colDivisor, dims);
		// vector<Mat> blocks2;
		//split( y2, blocks2 );

		//			for (int i = 0; i < 8; i++)
		//	cout <<  (float)y_.at<uchar>(0, i) << ",";
		//cout << endl;

			/*  for(int y = 0; y < y_.rows; y += 1)
              {
				  for (int x = 0; x < y_.cols - 8; x += 1)
					{
						if (y_.at<uchar>(y, x) == 54
							&& y_.at<uchar>(y , x +1 ) == 53
							&& y_.at<uchar>(y, x + 2 ) == 52
							&& y_.at<uchar>(y , x  + 3) == 51
							&& y_.at<uchar>(y , x + 4 ) == 52
							&& y_.at<uchar>(y , x + 5 ) == 54
							&& y_.at<uchar>(y , x + 6 ) == 56
							&& y_.at<uchar>(y , x + 7 ) == 57)
							break;
					}
			  }*/

			//Mat tmp = y_.rowRange(0,1).colRange(120, 128);
	/*		int dims[] = {colDivisor,rowDivisor,8,8};
		Mat tmp = y_.reshape(1,colDivisor, dims);

		for (int i = 0; i < 8; i++)
			cout <<  (float)tmp.at<uchar>(0, i) << ",";
		cout << endl;

		for (int i = 0; i < 8; i++)
			cout <<  (float)tmp.at<uchar>(0,i) << ",";
		cout << endl;
*/
		//for (int i = 0; i < 8; i++)
		//	cout <<  (float)blocks2[1].at<uchar>(i,0) << ",";
		//cout << endl;

		//for (int i = 0; i < 8; i++)
		//	cout <<  (float)blocks2[1].at<uchar>(0,i) << ",";
		//cout << endl;


            // check if divisors fit to image dimensions
            if (y_.cols % colDivisor == 0 && y_.rows % rowDivisor == 0)
            {
                for (int y = 0; y < y_.cols; y += y_.cols / colDivisor)
                {
                    for(int x = 0; x < y_.rows; x += y_.rows / rowDivisor)
                    {
						if (y == 0 && x == 0)
						{
							cout <<  "x=" << x << ", y=" << y << endl;
							Mat bl = y_(cv::Rect(y, x, (y_.cols / colDivisor), (y_.rows / rowDivisor)));
							for(int y = 0; y < bl.rows; y += 1)
							  {
								  for (int x = 0; x < bl.cols; x += 1)
									{
										cout <<  (float)bl.at<uchar>(y,x) << ",";
									}
								  cout << endl;
							  }
						}
                        blocks.push_back(y_(cv::Rect(y, x, (y_.cols / colDivisor), (y_.rows / rowDivisor))).clone());
                    }
                }
            }

		//	int i = 0;
		//for (; i < 500; )
		//{
		//	if (i + 1 % 8 == 0)
		//		i =+ 80
		//	
		//	for (int j = 0; j < 8; j += 80)
		//	{
		//		cout <<  (float)y_.at<uchar>(i,j) << ",";
		//	}
		//	cout << endl;
		//}

			//for (int y = 0; y < 2; y += 120)
   //         {
			//	Mat block;
			//	block.create(8, 8, CV_32F);
   //             for(int x = 0; x < 8; x += 1)
   //             {
			//		block.at<float>(i,j) =  static_cast<float>(blocks[i].at<uchar>(i,j));
   //             }
			//	blocks.push_back(block);
   //         }

			//cout.setf(ios::hex, ios::basefield);
			//for (int i = 0; i < blocks[i].size().height; i++)
			//{
			//	cout << "i=" << i << " ";
			//	for (int j = 0; j < blocks[i].size().width; j++)
			//	{
			//		cout <<  (float)blocks[i].at<uchar>(i,j) << ",";
			//	}
			//	cout << endl;
			//}

			vector<double> qDCT;

			for (int i = 0; i < blocks.size(); i++)
			{
				Mat dct_result;
				//dct_result.create(8,8,CV_32F);
		//		Mat img3;
		//img3.create(8, 8, CV_32F);
		//Mat clone = blocks[i].clone();
		//clone.convertTo(img3, CV_32FC1);
				//blocks[i].convertTo(img3, CV_32F//); // also scale to [0..1] range (not mandatory)

				 // Read image
//Mat img = imread("d:\\Борисов\\5nnfwer7qkc.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//// Grayscale image is 8bits per pixel,
//// but dct() method wants float values!
//Mat img4 = Mat( img.rows, img.cols, CV_64F);
//img2.convertTo(img4, CV_64F);
//imshow("img.jpg", img4);
//
//// Let's do the DCT now: image => frequencies
//Mat freq;
//dct(img4, freq);
//
//// Save a visualization of the DCT coefficients
//imshow("dct.jpg", freq);

//If matrix is of type CV_8U then use Mat.at<uchar>(y,x).
//If matrix is of type CV_8S then use Mat.at<schar>(y,x).
//If matrix is of type CV_16U then use Mat.at<ushort>(y,x).
//If matrix is of type CV_16S then use Mat.at<short>(y,x).
//If matrix is of type CV_32S then use Mat.at<int>(y,x).
//If matrix is of type CV_32F then use Mat.at<float>(y,x).
//If matrix is of type CV_64F then use Mat.at<double>(y,x).

				//Mat img3;
				//img3.create(blocks[i].size(), CV_64F);
				//blocks[i].convertTo(img3, CV_64F);
				Mat img3 = Mat(blocks[i].rows, blocks[i].cols, CV_32F);
				blocks[i].convertTo(img3, CV_32F);
				img3.convertTo(img3, CV_32F);

				//for (int y = 0; y < blocks[i].size().height; y++)
				//{
				//	cout << "y=" << y << " ";
				//	for (int x = 0; x < blocks[i].size().width; x++)
				//	{
				//		//cout << blocks[i].at<uchar>(i,j) << endl;
				//		//float tmp = static_cast<float>(blocks[i].at<uchar>(i,j));
				//		//float tmp2 = (float)(blocks[i].at<uchar>(i,j));
				//		img3.at<float>(y,x) =  static_cast<float>(blocks[i].at<uchar>(y,x));
				//		//img3.at<float>(i,j) = tmp;
				//		//float check = img3.at<float>(i,j);
				//		//if (i == 0)
				//		cout << img3.at<float>(y,x) << ",";
				//	}
				//	cout << endl;
				//}

				// Grayscale image is 8bits per pixel,
// but dct() method wants float values!
//Mat img3 = Mat( img2.rows, img2.cols, CV_64F);
//img2.convertTo(img3, CV_64F);

				dct(img3, dct_result);
				cout << dct_result.type() << endl;

				cout <<  "dct" << endl;
				for(int y = 0; y < dct_result.rows; y += 1)
				{
					for (int x = 0; x < dct_result.cols; x += 1)
					{
						//uchar u = dct_result.at<cv::Vec3b>(y,x)[0];
						//cout <<  (float)dct_result.at<uchar>(y,x) << ",";
						cout <<  dct_result.at<float>(y,x) << ", ";
					}
					cout << endl;
				}

				//dct(blocks[i], dct_result);
				//qDCT.push_back(dct(blocks));
			}

//		 cv::Mat m2(ROWS, COLS*PLANES, CV_32SC1, m3.data); // no copying happening here
//cv::Mat m2xPlanes = m2.reshape(PLANES); // not sure if this involves a copy
//std::vector<Mat> planes;
//cv::split(m2xPlanes, planes); // usually used for splitting multi-channel matrices
//
//std::vector<int> flat;
//for(size_t i=0; i<planes.size(); i++) {
//    cv::Mat plane_i = planes[i];
//    const int* plane_i_ptr = plane_i.ptr<int>(0);
//    flat.insert(flat.end(), plane_i_ptr, plane_i_ptr+plane_i.total());
//}

		 for (int i = 0; i < h; i++)
		 {
		 }

		//return Error::OK;
		return ImageInfo();
	}

	ImageInfo Engine::ResizeAndCalculateImageMetric(const WChar* image, int width, int heigth)
	{
		return ImageInfo();
	}
}
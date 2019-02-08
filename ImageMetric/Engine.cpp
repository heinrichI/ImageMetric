#include "Engine.h"
#include "OpenCVHelper.h"
#include "Histogram.h"
#include "BHistogram.h"

#include <iostream>
#include <iomanip>

#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm> // for std::copy

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
			for(int x = 0; x < y_.rows; x += y_.rows / rowDivisor)
            
            {
                for (int y = 0; y < y_.cols; y += y_.cols / colDivisor)
                {
					if (y == 0 && x == 8)
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

					if (y == 8 && x == 0)
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


		/*cv::FileStorage file("block0.xml", cv::FileStorage::WRITE);
		file << "matName" << blocks[0];
		file.release();
		cv::FileStorage file1("block1.xml", cv::FileStorage::WRITE);
		file1 << "matName" << blocks[1];
		file1.release();
		cv::FileStorage file2("block2.xml", cv::FileStorage::WRITE);
		file2 << "matName" << blocks[2];
		file2.release();
		cv::FileStorage file3("block3.xml", cv::FileStorage::WRITE);
		file3 << "matName" << blocks[3];
		file3.release();
		cv::FileStorage file4("block4.xml", cv::FileStorage::WRITE);
		file4 << "matName" << blocks[4];
		file4.release();
		cv::FileStorage file5("block5.xml", cv::FileStorage::WRITE);
		file5 << "matName" << blocks[5];
		file5.release();
		cv::FileStorage file6("block6.xml", cv::FileStorage::WRITE);
		file6 << "matName" << blocks[6];
		file6.release();
		cv::FileStorage file7("block7.xml", cv::FileStorage::WRITE);
		file7 << "matName" << blocks[7];
		file7.release();
		cv::FileStorage file8("block8.xml", cv::FileStorage::WRITE);
		file8 << "matName" << blocks[8];
		file8.release();
		cv::FileStorage file9("block9.xml", cv::FileStorage::WRITE);
		file9 << "matName" << blocks[9];
		file9.release();

		cv::FileStorage file500("block500.xml", cv::FileStorage::WRITE);
		file500 << "matName" << blocks[500];
		file500.release();
		cv::FileStorage file9599("block9599.xml", cv::FileStorage::WRITE);
		file9599 << "matName" << blocks[9599];
		file9599.release();*/
		//imwrite( "block0", blocks[0] );


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

			vector<Mat> qDCT;

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
				//cout << dct_result.type() << endl;
				qDCT.push_back(dct_result.clone());

				//cout <<  "dct" << endl;
				//for(int y = 0; y < dct_result.rows; y += 1)
				//{
				//	for (int x = 0; x < dct_result.cols; x += 1)
				//	{
				//		//uchar u = dct_result.at<cv::Vec3b>(y,x)[0];
				//		//cout <<  (float)dct_result.at<uchar>(y,x) << ",";
				//		cout <<  dct_result.at<float>(y,x) << ", ";
				//	}
				//	cout << endl;
				//}

				//dct(blocks[i], dct_result);
				//qDCT.push_back(dct(blocks));
			}

		//cv::FileStorage file("qDCT0.xml", cv::FileStorage::WRITE);
		//file << "matName" << qDCT[0];
		//file.release();
		//cv::FileStorage file1("qDCT1.xml", cv::FileStorage::WRITE);
		//file1 << "matName" << qDCT[1];
		//file1.release();
		//cv::FileStorage file500("qDCT500.xml", cv::FileStorage::WRITE);
		//file500 << "matName" << qDCT[500];
		//file500.release();

			//vector<double> sum;
			//for (int i = 0; i < qDCT.size(); i++)
			//{
			//	double s = cv::sum( qDCT[i] )[0];
			//	sum.push_back(s);
			//}
		

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


		Mat row0;
		Mat row1;
		Mat row2;
		Mat row3;
		Mat row4;
		Mat row5;
		Mat row6;
		Mat row7;
		for each (Mat dct in qDCT)
		{
			//a(Range(0, a.rows), Range(a.cols - 2, a.cols)).copyTo(e);
			row0.push_back(dct.row(0));
			row1.push_back(dct.row(1));
			row2.push_back(dct.row(2));
			row3.push_back(dct.row(3));
			row4.push_back(dct.row(4));
			row5.push_back(dct.row(5));
			row6.push_back(dct.row(6));
			row7.push_back(dct.row(7));
		}


		//	Mat meanArray;
		//Scalar outMean = mean(qDCT[0]);
		Mat row_mean;
		//reduce(qDCT[0], row_mean, 0, CV_REDUCE_AVG);
		//reduce(row1, row_mean, 0, CV_REDUCE_AVG);
		//reduce(qDCT[0], col_mean, 1, CV_REDUCE_AVG);

		cv::Mat meanMat;

		reduce(row0, row_mean, 0, CV_REDUCE_AVG);
		meanMat.push_back(row_mean.clone());
		reduce(row1, row_mean, 0, CV_REDUCE_AVG);
		meanMat.push_back(row_mean.clone());
		reduce(row2, row_mean, 0, CV_REDUCE_AVG);
		meanMat.push_back(row_mean.clone());
		reduce(row3, row_mean, 0, CV_REDUCE_AVG);
		meanMat.push_back(row_mean.clone());
		reduce(row4, row_mean, 0, CV_REDUCE_AVG);
		meanMat.push_back(row_mean.clone());
		reduce(row5, row_mean, 0, CV_REDUCE_AVG);
		meanMat.push_back(row_mean.clone());
		reduce(row6, row_mean, 0, CV_REDUCE_AVG);
		meanMat.push_back(row_mean.clone());
		reduce(row7, row_mean, 0, CV_REDUCE_AVG);
		meanMat.push_back(row_mean.clone());

		//cv::FileStorage file("mean.xml", cv::FileStorage::WRITE);
		//file << "matName" << meanMat;
		//file.release();

		//cout << meanMat << endl;

		//cv::Mat meanMat = cv::repeat(row_mean, qDCT[0].rows, 1);

		/*for(int y = 0; y < meanMat.rows; y += 1)
		{
			for (int x = 0; x < meanMat.cols; x += 1)
			{
				cout <<  meanMat.at<float>(y,x) << ", ";
			}
			cout << endl;
		}*/

		vector<Mat> subAll;
		Mat sub;
		//subtract(qDCT[0].row(0), row_mean, sub);
		//subtract(qDCT[0], meanMat, sub);
		for each (Mat dct in qDCT)
		{
			subtract(dct, meanMat, sub);
			Mat conv;
			sub.convertTo(conv, CV_32S);
			subAll.push_back(conv);
		}

		//cv::FileStorage file("subtract0.xml", cv::FileStorage::WRITE);
		//file << "matName" << subAll[0];
		//file.release();

		//cv::FileStorage file2("subtract1.xml", cv::FileStorage::WRITE);
		//file2 << "matName" << subAll[1];
		//file2.release();

		//cv::FileStorage file500("subtract500.xml", cv::FileStorage::WRITE);
		//file500 << "matName" << subAll[500];
		//file500.release();

		//cv::FileStorage file9599("subtract9599.xml", cv::FileStorage::WRITE);
		//file9599 << "matName" << subAll[9599];
		//file9599.release();

		//cout << subAll[0] << endl;

		
		//цикл по первым трем числам блоков

		vector<int> data;
		for each (Mat sub in subAll)
		{
			data.push_back(sub.at<int>(0,0));
		}

		//std::ofstream output_file("data.txt");
		//std::ostream_iterator<int> output_iterator(output_file, "\n");
		//std::copy(data.begin(), data.end(), output_iterator);
		//output_file.close();

		int max = *std::max_element(data.begin(), data.end());
		int min = *std::min_element(data.begin(), data.end());

		/*vector<int> minMaxArray;
		for (int i = min; i <= max; i++)
		{
			minMaxArray.push_back(i);
		}*/
		
		//static const int arr[] = { -915, -908, -907, -907, -907, -907, -907, -907, -907, -905, -899, -899, -899, -899, -899, -898, -898, -898, -898, -898, -898, -898, -898, -898, -898, -898, -897 };
		//vector<int> testData (arr, arr + sizeof(arr) / sizeof(arr[0]) );

		//std::ifstream is("testdata");
		//std::istream_iterator<int> start(is), end;
		//std::vector<int> testData(start, end);
		//std::cout << "Read " << testData.size() << " numbers" << std::endl;

		// print the numbers to stdout
		//std::cout << "numbers read in:\n";
		//std::copy(numbers.begin(), numbers.end(), 
		//std::ostream_iterator<double>(std::cout, " "));
		//std::cout << std::endl;

		//Histogram histogram(data);
		//Histogram histogram(minMaxArray.size(), min, max, 0);
		
		//BHistogram histogram(data);

		/// Establish the number of bins
		int histSize = max - min;
		/// Set the ranges ( for B,G,R) )
		float range[] = { min, max } ;
		const float* histRange = { range };
		bool uniform = true; 
		bool accumulate = false;
		Mat b_hist;

//cv::Mat converted(1, data.size(), CV_32S, data);
		Mat converted(data);
		converted.convertTo(converted, CV_32F);
		//cout << converted << endl;

//&bgr_planes[0]: The source array(s)
//1: The number of source arrays (in this case we are using 1. We can enter here also a list of arrays )
//0: The channel (dim) to be measured. In this case it is just the intensity (each array is single-channel) so we just write 0.
//Mat(): A mask to be used on the source array ( zeros indicating pixels to be ignored ). If not defined it is not used
//b_hist: The Mat object where the histogram will be stored
//1: The histogram dimensionality.
//histSize: The number of bins per each used dimension
//histRange: The range of values to be measured per each dimension
//uniform and accumulate: The bin sizes are the same and the histogram is cleared at the beginning.
		calcHist( &converted, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

		double minHist, maxHist;
		cv::minMaxLoc(b_hist, &minHist, &maxHist);
		double s = cv::sum( b_hist )[0];
		//cout << b_hist << endl;

		//cv::FileStorage fileHist("hist.xml", cv::FileStorage::WRITE);
		//fileHist << "matName" << b_hist;
		//fileHist.release();

		//Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
		/// Normalize the result to [ 0, histImage.rows ]
		normalize(b_hist, b_hist, 0, 1, NORM_MINMAX, -1, Mat() );
		//cout << b_hist << endl;

		//cv::FileStorage file("hist.xml", cv::FileStorage::WRITE);
		//file << "matName" << b_hist;
		//file.release();
		
		/*
		Mat C = (Mat_<float>(1,11) << 0.00010416666666666667, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.00010416666666666667, 0.0007291666666666667, 0.0, 0.00010416666666666667);
		//cout << C << endl;
		 
		//dft(C, C, DFT_COMPLEX_OUTPUT);
		//cout << C << endl;

		//Mat padded;                            //expand input image to optimal size
		//int m = getOptimalDFTSize( C.rows );
		//int n2 = getOptimalDFTSize( C.cols ); // on the border add zero values
		//copyMakeBorder(C, padded, 0, m - C.rows, 0, n2 - C.cols, BORDER_CONSTANT, Scalar::all(0));
		//Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
		Mat planes[] = {Mat_<float>(C), Mat::zeros(C.size(), CV_32F)};

		Mat complexI;
		merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
		dft(complexI, complexI, DFT_COMPLEX_OUTPUT);            // this way the result may fit in the source matrix
		//cout << complexI << endl;
		// compute the magnitude and switch to logarithmic scale
		// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
		split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
		//cout << planes[0] << endl;
		//cout << planes[1] << endl;

		// create a new matrix for storage
		//cv::Mat absol = cv::Mat::zeros(complexI.size(), complexI.type());
		//for(int i=0;i<absol.rows;i++){
		//  // pointer to row(i) values
		//  const float* rowi_x = planes[0].ptr<float>(i);
		//  const float* rowi_y = planes[1].ptr<float>(i); 
		//  float* rowi_a = absol.ptr<float>(i); 
		//  for(int j=0;j<=absol.cols;j++){ 
		//	 rowi_a[j] = sqrt(rowi_x[j]*rowi_x[j]+rowi_y[j]*rowi_y[j]);
		//  }
		//}
		//cout << absol << endl;

		//Mat mul;
		//mulSpectrums(complexI, complexI, mul, 0, false);
		//mulSpectrums(complexI, complexI, mul, 0, true);
		//cout << mul << endl;
		//mulSpectrums(planes[0], planes[1], mul, 0, true);
		//mulSpectrums(planes[0], planes[1], mul, 0, false);
		//cout << mul << endl;

		magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
		Mat magI = planes[0];
		//cout << magI << endl; //absolute value
		//cout << planes[1] << endl;

		//magI += Scalar::all(1);                    // switch to logarithmic scale
		//log(magI, magI);
		//cout << magI << endl;

		*/

		Mat planes2[] = {Mat_<float>(b_hist), Mat::zeros(b_hist.size(), CV_32F)};
		Mat complexI2;
		merge(planes2, 2, complexI2);         // Add to the expanded another plane with zeros
		dft(complexI2, complexI2, DFT_COMPLEX_OUTPUT);   
		split(complexI2, planes2);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
		magnitude(planes2[0], planes2[1], planes2[0]);// planes[0] = magnitude
		Mat magI2 = planes2[0];

		//dft(b_hist, b_hist );
		//cout << "dft" << endl;
		//cout << b_hist << endl;

		cv::FileStorage fileZ("z.xml", cv::FileStorage::WRITE);
		fileZ << "matName" << magI2;
		fileZ.release();
		
		try
		{
		//Mat rotated(b_hist.size(), b_hist.type());
		//Mat rotated(b_hist);
		cv::Mat rotated = cv::Mat::zeros(magI2.size(), magI2.type());
		//int halfWidth = b_hist.rows / 2;
		magI2(cv::Rect(0, 0, magI2.cols, magI2.rows / 2)).copyTo(rotated(cv::Rect(0, magI2.rows / 2, magI2.cols, magI2.rows / 2)));
		magI2(cv::Rect(0,  magI2.rows / 2, magI2.cols, magI2.rows / 2)).copyTo(rotated(cv::Rect(0, 0, magI2.cols, magI2.rows / 2)));
		//cout << rotated << endl;
		//b_hist(cv::Rect(b_hist.cols / 2, 0, b_hist.cols / 2, b_hist.rows)).copyTo(rotated(cv::Rect(0, 0, b_hist.cols / 2, b_hist.rows)));
		//Mat rotated(Range(rowRange), Range(colRange))
		//cv::Mat out = cv::Mat::zeros(b_hist.size(), b_hist.type());
		//b_hist(cv::Rect(0,10, b_hist.cols, b_hist.rows-10)).copyTo(out(cv::Rect(0,0,b_hist.cols,b_hist.rows-10)));
		cv::Mat shifted = cv::Mat::zeros(rotated.size(), rotated.type());
		rotated(cv::Rect(0, 1, magI2.cols, magI2.rows - 1)).copyTo(shifted(cv::Rect(0, 0, magI2.cols, magI2.rows - 1)));
		rotated(cv::Rect(0, magI2.rows - 1, magI2.cols, 1)).copyTo(shifted(cv::Rect(0, magI2.rows - 1, magI2.cols, 1)));

		Mat subtracted;
		subtract(shifted, rotated, subtracted);
		//cout << subtracted << endl;

		
		vector<int> indices;
		for (int y = 0; y < subtracted.rows - 1; y += 1)
        {
			//cout <<  (float)subtracted.at<float>(y,0) << ",";
			if (subtracted.at<float>(y,0) > 0 && subtracted.at<float>(y+1,0) < 0)
			{
				cout <<  (float)subtracted.at<float>(y,0) << ">" << (float)subtracted.at<float>(y+1,0) << "(" << y << "), ";
				indices.push_back(y + 1);
			}
		}

		int peakCount = 0;
		for (int i = 0; i < indices.size(); i++)
        {
			if ((float)rotated.at<float>(indices[i],0) > 0.5)
				peakCount++;
		}

		}
		catch (cv::Exception& e) 
		{
			cerr << "Error Reason: " << e.msg << endl;
			// nothing more we can do
			exit(1);
		}



		//for(int y = 0; y < sub.rows; y += 1)
		//{
		//	for (int x = 0; x < sub.cols; x += 1)
		//	{
		//		cout <<  sub.at<float>(y,x) << ", ";
		//	}
		//	cout << endl;
		//}

		//Mat qDCTConv;
		//qDCTConv.create(sub.rows, sub.cols, CV_32S);
		//sub.convertTo(qDCTConv, CV_32S);

		//for(int y = 0; y < qDCTConv.rows; y += 1)
		//{
		//	for (int x = 0; x < qDCTConv.cols; x += 1)
		//	{
		//		cout <<  qDCTConv.at<int>(y,x) << ", ";
		//	}
		//	cout << endl;
		//}


		//return Error::OK;
		return ImageInfo();
	}

	ImageInfo Engine::ResizeAndCalculateImageMetric(const WChar* image, int width, int heigth)
	{
		return ImageInfo();
	}
}
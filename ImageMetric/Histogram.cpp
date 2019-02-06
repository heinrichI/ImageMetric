#include "Histogram.h"

#include <algorithm>

using namespace std;


//#################################### CONSTRUCTOR #####################################//
//Histogram::Histogram(int numberOfBins, double minValue, double maxValue, double initialValue)
//	:max(maxValue),min(minValue),numberOfBins(numberOfBins)
//{
//	// Initialization of Member Variables //
//	binWidth		= (max - min)/numberOfBins;
//	pHistogramArray	= new double[numberOfBins];
//
//	//Initialization of Histogram_Array//
//	for (int i = 0; i < numberOfBins; i++) 
//		pHistogramArray[i] = initialValue;
//}

Histogram::Histogram(std::vector<int> & data)
{
	int numberOfSamples, index, numberOfBins;
    double binWidth, rangeSize, tempData;
    std::vector<int> binNumbers;
    //std::vector<double> data;
	int max;
	int min;


	max = *std::max_element(data.begin(), data.end());
	min = *std::min_element(data.begin(), data.end());

	
    numberOfSamples = data.size();
    //binSize = aBinSize;

    rangeSize = max - min;
    numberOfBins = max - min;
	//pHistogramArray	= new double[numberOfBins];
	HistogramVector.resize(numberOfBins + 1);

	binWidth = (max - min)/numberOfBins;
	//numberOfBins = ceil(rangeSize/binSize);
    //binNumbers.resize(numberOfBins);

	// initialize original index locations
  //vector<size_t> idx(data.size());
  //iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  //sort(idx.begin(), idx.end(),
  //     [&data](size_t i1, size_t i2) {return data[i1] < data[i2];});


	vector<int> sorted(data);
	std::sort(sorted.begin(), sorted.end());

	//vector<int> searchSorted;

	//vector<int> idx(rangeSize);
	//iota(idx.begin(), idx.end(), min);

	//for(int i = 0; i < sorted.size(); i++)
	//{
	//	auto iter = lower_bound( idx.begin(), idx.end(), sorted[i] );
	//	searchSorted.push_back(iter - idx.begin());
	//}

	vector<int> searchSorted2;
	for(int search_value = min; search_value < max; search_value++)
	{
		//auto it = my_find(cloned.begin(), cloned.end(), i); //it is your iterator
		//auto it = largest_less_than_or_equal_to(cloned.begin(), cloned.end(), i);

		auto iter = lower_bound( sorted.begin(), sorted.end(), search_value );
		searchSorted2.push_back(iter - sorted.begin());
	}


  //  for(int i = 0; i<numberOfSamples; i++){
  //      tempData = data[i] - min;
  //      index = (int)floor(tempData/binWidth);
		//HistogramVector[index] += 1; 
  //  }

	//double maxH = *std::max_element(HistogramVector.begin(), HistogramVector.end());
	//double minH = *std::min_element(HistogramVector.begin(), HistogramVector.end());
	//for each (double item in HistogramVector)
	//{
	//	item = (item - minH) / (maxH - minH);
	//}

	//normalize(HistogramVector);
	//normalized = (x-min(x))/(max(x)-min(x))
}

//#################################### DESTRUCTOR #####################################//	
Histogram::~Histogram()
{
	//delete [] pHistogramArray;
}

//################################## RESET HISTOGRAM ##################################//
//void Histogram::resetHistogramTo(double resetValue)
//{
//	for (int i = 0; i < numberOfBins; i++) 
//		pHistogramArray[i] = resetValue;
//}

//################################# UPDATE HISTOGRAM #################################//				
//void Histogram::updateAtValueByIncrement(double value, double increment)
//{
//	int index  = (int)((value - min)/binWidth);
//	
//	if( value < max && value > min)
//	{
//		pHistogramArray[index] += increment;
//	}
//	else
//	{
//		cout << value << " Value out of range!\n";
//	}
//}

//void Histogram::updateAtIndexByIncrement(int index, double increment)
//{
//	if(index >= numberOfBins)
//	{
//		cout << "Index out of range!\n";
//	}
//	else
//	{
//		pHistogramArray[index] += increment;
//	}
//}

//void Histogram::setValueAtIndexTo(int index, double value)
//{
//	pHistogramArray[index] = value;
//}

//################################# GET VALUE ########################################//		

//double Histogram::getValueAtValue(double value)
//{	
//	int index		= (int)((value - min)/binWidth);
//	return pHistogramArray[index];
//}
//
//double Histogram::getValueAtIndex(int index)
//{
//	return pHistogramArray[index];
//}	
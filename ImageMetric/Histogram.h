//Generic Histogram Base Class - Derived classes can extend functionality//
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;


class Histogram
{
	public:
		vector<double> HistogramVector;

		//######################## DESIGNATED CONSTRUCTOR/DESTRUCTOR ##########################//
		//Initializes the histogram with "numberOfBins" bins in the range (min_value,max_value)//																			
		//Histogram(int numberOfBins, double minValue, double maxValue, double initialValue);
		Histogram(std::vector<int> & data);
		~Histogram();
		
		//############################## RESET ######################################//
		//void   resetHistogramTo(double resetValue);		

		//############################# SETTERS #####################################//					        
		//void   updateAtValueByIncrement(double value, double increment);					
		//void   updateAtIndexByIncrement(int index, double increment);
		//void   setValueAtIndexTo(int index, double value);

		//############################# GETTERS #####################################//
		//double getValueAtValue(double value);												
		//double getValueAtIndex(int index);										
		//
		//double getBinWidth()const{return binWidth;}
		//double getMax()const{return max;}
		//double getMin()const{return min;}
		//int getNumberOfBins()const{return numberOfBins;}

		template<typename Iter, typename T>
		Iter my_find(Iter begin, Iter end, T value)
		{
			Iter i = std::lower_bound(begin, end, value);

			if (i != end && *i == value)
				return i; // found in container
			else
				return end; // not found
		}

		template <class ForwardIterator, class T>
		ForwardIterator largest_less_than_or_equal_to ( ForwardIterator first, ForwardIterator last,
		const T& value)
		{
			ForwardIterator upperb = upper_bound(first, last, value);
    
			// First element is >, so none are <=
			if(upperb == first)
			  return last;
    
			// All elements are <=, so return the smallest.
			if(upperb == last)
			  return --upperb;
    
			return upperb - 1;
		}


	protected:
		//double *pHistogramArray;		

		//int _max;
		//int _min;
		double binWidth;
		int _numberOfBins;

		void normalize(vector<double> & mat) 
		{
			auto minmax = std::minmax_element( mat.begin(), mat.end() );

			// (x-min(x))/(max(x)-min(x))
			//auto x = *minmax.first / ( *minmax.second - *minmax.first );
			
			double min = *minmax.first;
			double max = *minmax.second;
			auto div = max - min;

			for ( auto &value : mat ) 
				value = (value - min) / div;

			//std::transform(std::begin(mat), std::end(mat), std::begin(mat),
			//			[sum](double x) { return x / sum; });

			//std::for_each(std::begin(mat), std::end(mat),
			//	[](double &item) 
			//	{
			//		//double sum = std::accumulate(std::begin(item), std::end(item), 0.0);
			//		std::transform(std::begin(item), std::end(item), std::begin(item),
			//			[sum](double x) { return x / sum; });
			//	});
		}
};		

#endif

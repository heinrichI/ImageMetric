//#include "BHistogram.h"
//
//#include <algorithm>           // std::for_each
//#include <boost/format.hpp>    // only needed for printing
//#include "boost/histogram.hpp" // make_histogram, weight, indexed
//#include <cassert>             // assert
//#include <functional>          // std::ref
//#include <sstream>             // std::ostringstream, std::cout, std::flush
//
//using namespace std;
//
//using namespace boost::histogram; // strip the boost::histogram prefix 
//
//
//BHistogram::Histogram(std::vector<int> & data)
//{
//	 /*
//    Create a 1d-histogram with an axis that has 6 equidistant
//    bins on the real line from -1.0 to 2.0, and label it as "x".
//  */
//  auto h = make_histogram(axis::regular<>(6, -1.0, 2.0, "x"));
//
//  /*
//    Fill histogram with data, typically this happens in a loop.
//
//    A regular axis is a sequence of semi-open bins. Extra under- and
//    overflow bins extend the axis in the default configuration.
//    index    :      -1     0     1    2    3    4    5    6
//    bin edges:  -inf  -1.0  -0.5  0.0  0.5  1.0  1.5  2.0  inf
//
//    STL algorithms are supported. std::for_each is very convenient
//    to fill a histogram from an iterator range. Make sure to
//    use std::ref in the call, otherwise it will fill a copy of
//    the histogram and return it, which is less efficient.
//  */
//
//  auto data = {-0.5, 1.1, 0.3, 1.7};
//  std::for_each(data.begin(), data.end(), std::ref(h));
//  h(-1.5); // put in underflow bin -1
//  h(-1.0); // put in bin 0, bin interval is semi-open
//  h(2.0);  // put in overflow bin 6, bin interval is semi-open
//  h(20.0); // put in overflow bin 6
//
//  /*
//    This does a weighted fill using the `weight` function as an additional argument. It
//    may appear at the beginning or end of the argument list. C++ doesn't have keyword
//    arguments, this is the next-best thing.
//  */
//  h(0.1, weight(1.0));
//
//  /*
//    Iterate over bins with the `indexed` range adaptor to obtain the current bin index and
//    the bin value via an accessor class. By default, under- and overflow bins are skipped.
//    Passing `coverage::all` as the optional second argument iterates over all bins.
//
//    - Access the value with the dereference operator. The proxy acts like a pointer to it.
//    - Access the current index with `index(d)` of the accessor, passing the dimension d.
//    - Access the corresponding bin interval view with `bin(d)`. Use a compile-time number
//      like 1_c instead of a normal number like 1, if possible, to make this call more
//      efficent. The return type depends on the axis type (see the axis reference for
//      details), usually a class that represents a semi-open interval, whose edges can be
//      accessed with methods `lower()` and `upper()`.
//    - Iteration order is implementation defined, `indexed` uses the most efficient one.
//  */
//  using namespace boost::histogram::literals; // import compile-time numbers 0_c, 1_c, ...
//
//  std::ostringstream os;
//  for (auto x : indexed(h, coverage::all)) {
//    os << boost::format("bin %2i [%4.1f, %4.1f): %i\n") % x.index() % x.bin().lower() %
//              x.bin().upper() % *x;
//  }
//
//  std::cout << os.str() << std::flush;
//
//  assert(os.str() == "bin -1 [-inf, -1.0): 1\n"
//                     "bin  0 [-1.0, -0.5): 1\n"
//                     "bin  1 [-0.5, -0.0): 1\n"
//                     "bin  2 [-0.0,  0.5): 2\n"
//                     "bin  3 [ 0.5,  1.0): 0\n"
//                     "bin  4 [ 1.0,  1.5): 1\n"
//                     "bin  5 [ 1.5,  2.0): 1\n"
//                     "bin  6 [ 2.0,  inf): 2\n");
//  // note how under- and overflow bins appear at the end 
//}

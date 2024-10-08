/*=================================================================
 * arrayFillSetPr.c - example used to illustrate how to fill an mxArray
 *
 * Create an empty mxArray. Create a dynamic data array and
 * copy your data into it. Use mxSetDoubles (or mxSetPr for separate complex
 * MEX files) to dynamically allocate memory
 * as you fill mxArray with the contents of "dynamicData".
 *
 * Input:   none
 * Output:  mxArray
 *
 * Copyright 2008-2018 The MathWorks, Inc.
 *
 *=================================================================*/

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

/* The mxArray in this example is 2x2 */
static constexpr std::size_t ROWS    = 2;
static constexpr std::size_t COLUMNS = 2;

void mex::Function::operator()(mx::Span<mx::Array>, mx::View<mx::ArrayCref>)
{
  static constexpr std::array<std::complex<double>, 4> data{{{2.1, 2.1}, {3.4, 3.4}, {2.3, 2.3}, {2.45, 2.45}}}; /* existing data */

  static_assert(data.size() == ROWS * COLUMNS);

  throw mx::Exception{"MATLAB:arrayFillSetPr:unsupported", "matlab-cpp-wrapper currently does not support setting matrix data."};
}

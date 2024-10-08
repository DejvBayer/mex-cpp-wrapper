/*=================================================================
 * mxcreateuninitnumericmatrix.c
 * Create an uninitialized mxArray, fill it with the contents
 * of "data", and return it in plhs[0].
 *
 * Input:   none
 * Output:  mxArray
 *
 * Copyright 2015-2018 The MathWorks, Inc.
 *
 *=================================================================*/

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

/* The mxArray in this example is 2x2 */
static constexpr std::size_t ROWS    = 2;
static constexpr std::size_t COLUMNS = 2;

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  static constexpr std::array data{2.1, 3.4, 2.3, 2.45}; /* existing data */

  /* Check for proper number of arguments. */
  if (!rhs.empty())
  {
    throw mx::Exception{"MATLAB:mxcreateuninitnumericmatrix:rhs", "This function takes no input arguments."};
  }

  /* Create an m-by-n mxArray. */
  auto array = mx::makeUninitNumericArray<double>(ROWS, COLUMNS);

  /* Copy existing data. */
  std::copy(data.begin(), data.end(), array.begin());

  lhs[0] = std::move(array);
}

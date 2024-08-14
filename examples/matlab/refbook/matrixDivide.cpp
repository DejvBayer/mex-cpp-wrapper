/*=========================================================
 * matrixDivide.c - Example for illustrating how to use 
 * LAPACK within a C MEX-file.
 *
 * X = matrixDivide(A,B) computes the solution to a 
 * system of linear equations A * X = B
 * using LAPACK routine DGESV, where 
 * A is a real N-by-N matrix.
 * X and B are real N-by-1 matrices.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 2009-2018 The MathWorks, Inc.
 *=======================================================*/

#include <vector>

#include <lapack.h>

#include <mex/mex.hpp>
#include <mex/Function.hpp>

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{
  /* Check for proper number of arguments. */
  if (rhs.size() != 2)
  {
    throw mex::Exception{"MATLAB:matrixDivide:rhs", "This function requires 2 input matrices."};
  }

  /* check to make sure the first input argument is a real matrix */
  if (!rhs[0].isDouble() || rhs[0].isComplex())
  {
    throw mex::Exception{"MATLAB:matrixDivide:fieldNotRealMatrix", "First input argument must be a real, double matrix."};
  }
  /* check to make sure the second input argument is a real matrix */
  if (!rhs[1].isDouble() || rhs[1].isComplex())
  {
    throw mex::Exception{"MATLAB:matrixDivide:fieldNotRealMatrix", "Second input argument must be a real, double matrix."};
  }
  
  /* Validate matrix input arguments */
  const double* A = mex::NumericArrayCref<double>{rhs[0]}.getData(); /* pointer to first input matrix */
  const double* B = mex::NumericArrayCref<double>{rhs[1]}.getData(); /* pointer to second input matrix */

  /* dimensions of input matrices */
  const std::ptrdiff_t m = static_cast<std::ptrdiff_t>(rhs[0].getM());
  const std::ptrdiff_t p = static_cast<std::ptrdiff_t>(rhs[0].getN());
  const std::ptrdiff_t n = static_cast<std::ptrdiff_t>(rhs[1].getN());

  if (p != rhs[1].getM())
  {
    throw mex::Exception{"MATLAB:matrixDivide:matchdims", "Inner dimensions of matrices do not match."};
  }
  if (p != m)
  {
    throw mex::Exception{"MATLAB:matrixDivide:square", "LAPACK function requires input matrix 1 must be square."};
  }
  if (n != 1)
  {
    throw mex::Exception{"MATLAB:matrixDivide:zerodivide", "For this example input matrix 2 must be a column vector."};
  }

  /* DGESV works in-place, so we copy the inputs first. */
  std::vector<double> Awork{mex::NumericArrayCref<double>{rhs[0]}.begin(), mex::NumericArrayCref<double>{rhs[0]}.end()};

  double* A2 = Awork.data();

  /* Create output for DGESV */
  auto output = mex::makeUninitNumericArray<double>(p, n);
  std::copy_n(B, p * n, output.begin());

  double* B2 = output.getData();

  /* Create inputs for DGESV */
  std::vector<std::ptrdiff_t> pivot(m * p);

  std::ptrdiff_t info{};

  /* Call LAPACK */
  dgesv(&m, &n, A2, &m, pivot.data(), B2, &p, &info);
  
  lhs[0] = std::move(output);
}

/*
  This file is part of matlab-cpp-wrapper library.

  Copyright (c) 2024 David Bayer

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef MATLABW_MX_OBJECT_ARRAY_HPP
#define MATLABW_MX_OBJECT_ARRAY_HPP

#include "detail/include.hpp"

#include "Array.hpp"
#include "StructArray.hpp"

namespace matlabw::mx
{
  /**
   * @brief Create an object array
   * @param dims Dimensions of the object array
   * @return ObjectArray
   */
  [[nodiscard]] inline Array makeObjectArray(StructArray&& srcArray, const char* className)
  {
    if (!srcArray.isValid())
    {
      throw Exception{"invalid source array"};
    }

    if (className == nullptr)
    {
      throw Exception{"invalid class name"};
    }

    if (mxSetClassName(srcArray.release(), className))
    {
      throw Exception{"failed to set class name"};
    }

    return Array{std::move(srcArray)};
  }

  /**
   * @brief Create an object array from a StructArray
   * @param srcArray Source array
   * @param className Class name. Must be null-terminated.
   * @return ObjectArray
   */
  [[nodiscard]] inline Array makeObjectArray(StructArray&& srcArray, std::string_view className)
  {
    return makeObjectArray(std::move(srcArray), className.data());
  }
} // namespace matlabw::mx

#endif /* MATLABW_MX_OBJECT_ARRAY_HPP */

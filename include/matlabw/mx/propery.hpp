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

#ifndef MATLABW_MX_PROPERTY_HPP
#define MATLABW_MX_PROPERTY_HPP

#include "detail/include.hpp"

#include "ArrayRef.hpp"
#include "common.hpp"
#include "Exception.hpp"

namespace matlabw::mx
{
  /**
   * @brief Gets the property of the object
   * @param array Array
   * @param index Index
   * @param propName Property name
   * @return Property value
   */
  [[nodiscard]] inline std::optional<ArrayCref> getProperty(const ArrayRef    array,
                                                            const std::size_t index,
                                                            const char* const propName)
  {
    if (propName == nullptr)
    {
      throw Exception{"property name must not be null"};
    }

    mxArray* prop = mxGetProperty(array.get(), index, propName);

    if (prop == nullptr)
    {
      return std::nullopt;
    }

    return ArrayCref{prop};
  }
  
  /**
   * @brief Gets the property of the object
   * @param array Array
   * @param index Index
   * @param propName Property name. Must be null-terminated.
   * @return Property value
   */
  [[nodiscard]] inline std::optional<ArrayCref> getProperty(const ArrayRef         array,
                                                            const std::size_t      index,
                                                            const std::string_view propName)
  {
    return getProperty(array, index, propName.data());
  }

  /**
   * @brief Gets the property of the object
   * @param array Array
   * @param propName Property name
   * @return Property value
   */
  [[nodiscard]] inline std::optional<ArrayCref> getProperty(const ArrayRef    array,
                                                            const char* const propName)
  {
    return getProperty(array, 0, propName);
  }

  /**
   * @brief Gets the property of the object
   * @param array Array
   * @param propName Property name. Must be null-terminated.
   * @return Property value
   */
  [[nodiscard]] inline std::optional<ArrayCref> getProperty(const ArrayRef         array,
                                                            const std::string_view propName)
  {
    return getProperty(array, 0, propName.data());
  }

  /**
   * @brief Sets the property of the object
   * @param array Array
   * @param index Index
   * @param propName Property name
   * @param value Property value
   */
  inline void setProperty(const ArrayRef    array,
                          const std::size_t index,
                          const char* const propName,
                          const ArrayCref   value)
  {
    if (propName == nullptr)
    {
      throw Exception{"property name must not be null"};
    }

    mxSetProperty(array.get(), index, propName, value.get());
  }

  /**
   * @brief Sets the property of the object
   * @param array Array
   * @param index Index
   * @param propName Property name. Must be null-terminated.
   * @param value Property value
   */
  inline void setProperty(const ArrayRef         array,
                          const std::size_t      index,
                          const std::string_view propName,
                          const ArrayCref        value)
  {
    setProperty(array, index, propName.data(), value);
  }

  /**
   * @brief Sets the property of the object
   * @param array Array
   * @param propName Property name
   * @param value Property value
   */
  inline void setProperty(const ArrayRef    array,
                          const char* const propName,
                          const ArrayCref   value)
  {
    setProperty(array, 0, propName, value);
  }

  /**
   * @brief Sets the property of the object
   * @param array Array
   * @param propName Property name. Must be null-terminated.
   * @param value Property value
   */
  inline void setProperty(const ArrayRef         array,
                          const std::string_view propName,
                          const ArrayCref        value)
  {
    setProperty(array, 0, propName.data(), value);
  }
} // namespace matlabw::mx

#endif /* MATLABW_MX_PROPERTY_HPP */

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

#ifndef MATLABW_MEX_VARIABLE_HPP
#define MATLABW_MEX_VARIABLE_HPP

#include "detail/include.hpp"

namespace matlabw::mex
{
  /// @brief The workspace enumeration.
  enum class Workspace
  {
    base,   ///< The base workspace.
    global, ///< The global workspace.
    caller, ///< The caller workspace.
  };

  /**
   * @brief Get the name of the workspace.
   * @param workspace The workspace enumeration.
   * @return The name of the workspace.
   */
  [[nodiscard]] constexpr const char* getWorkspaceName(Workspace workspace)
  {
    switch (workspace)
    {
    case Workspace::base:
      return "base";
    case Workspace::global:
      return "global";
    case Workspace::caller:
      return "caller";
    default:
      throw mx::Exception{"invalid workspace"};
    }
  }

  /**
   * @brief Put a variable into the specified workspace.
   * @param workspace The workspace into which to put the variable.
   * @param name The name of the variable to put.
   * @param value The reference to the variable value.
   */
  inline void putVariable(Workspace workspace, const char* name, mx::ArrayCref value)
  {
    if (name == nullptr)
    {
      throw mx::Exception{"invalid variable name"};
    }

    const char* workspaceName = getWorkspaceName(workspace);

    if (mexPutVariable(workspaceName, name, value.get()) != 0)
    {
      throw mx::Exception{"failed to put variable"};
    }
  }

  /**
   * @brief Put a variable into the specified workspace.
   * @param workspace The workspace into which to put the variable.
   * @param name The name of the variable to put. Must be null-terminated.
   * @param value The reference to the variable value.
   */
  inline void putVariable(Workspace workspace, std::string_view name, mx::ArrayCref value)
  {
    putVariable(workspace, name.data(), value);
  }

  /**
   * @brief Get a variable reference from the specified workspace.
   * @param workspace The workspace from which to get the variable.
   * @param name The name of the variable to get.
   * @return The reference to the variable value.
   */
  [[nodiscard]] inline std::optional<mx::ArrayCref> getVariableCref(Workspace workspace, const char* name)
  {
    if (name == nullptr)
    {
      throw mx::Exception{"invalid variable name"};
    }

    const char* workspaceName = getWorkspaceName(workspace);

    const mxArray* array = mexGetVariablePtr(workspaceName, name);

    if (array == nullptr)
    {
      return std::nullopt;
    }

    return mx::ArrayCref{array};
  }

  /**
   * @brief Get a variable reference from the specified workspace.
   * @param workspace The workspace from which to get the variable.
   * @param name The name of the variable to get. Must be null-terminated.
   * @return The reference to the variable value.
   */
  [[nodiscard]] inline std::optional<mx::ArrayCref> getVariableCref(Workspace workspace, std::string_view name)
  {
    return getVariableCref(workspace, name.data());
  }

  /**
   * @brief Get a variable from the specified workspace.
   * @param workspace The workspace from which to get the variable.
   * @param name The name of the variable to get.
   * @return The copy of variable value.
   */
  [[nodiscard]] inline std::optional<mx::Array> getVariable(Workspace workspace, const char* name)
  {
    if (name == nullptr)
    {
      throw mx::Exception{"invalid variable name"};
    }

    const char* workspaceName = getWorkspaceName(workspace);

    mxArray* array = mexGetVariable(workspaceName, name);

    if (array == nullptr)
    {
      return std::nullopt;
    }
    
    return mx::Array{std::move(array)};
  }

  /**
   * @brief Get a variable from the specified workspace.
   * @param workspace The workspace from which to get the variable.
   * @param name The name of the variable to get. Must be null-terminated.
   * @return The copy of variable value.
   */
  [[nodiscard]] inline std::optional<mx::Array> getVariable(Workspace workspace, std::string_view name)
  {
    return getVariable(workspace, name.data());
  }
} // namespace matlabw::mex

#endif /* MATLABW_MEX_VARIABLE_HPP */

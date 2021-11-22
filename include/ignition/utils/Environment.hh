/*
 * Copyright (C) 2021 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef IGNITION_UTILS_ENVIRONMENT_HH_
#define IGNITION_UTILS_ENVIRONMENT_HH_

#include <ignition/utils/Export.hh>

#include <string>

namespace ignition
{
namespace utils
{

/// \brief Find the environment variable '_name' and return its value.
/// \param[in] _name Name of the environment variable.
/// \param[out] _value Value if the variable was found.
/// \param[in] _allowEmpty Allow set-but-empty variables.
///           (Unsupported on Windows)
/// \return True if the variable was found or false otherwise.
bool IGNITION_UTILS_VISIBLE env(
    const std::string &_name, std::string &_value,
    bool _allowEmpty=false);

/// \brief Set the environment variable '_name'.
///
/// Note that on Windows setting an empty string (_value=="")
/// is the equivalent of unsetting the variable.
///
/// \param[in] _name Name of the environment variable.
/// \param[in] _value Value of the variable to be set.
/// \return True if the variable was set or false otherwise.
bool IGNITION_UTILS_VISIBLE setenv(
    const std::string &_name, const std::string &_value);

/// \brief Unset the environment variable '_name'.
/// \param[in] _name Name of the environment variable.
/// \return True if the variable was unset or false otherwise.
bool IGNITION_UTILS_VISIBLE unsetenv(const std::string &_name);

}  // namespace utils
}  // namespace ignition

#endif  // IGNITION_UTILS_ENVIRONMENT_HH_


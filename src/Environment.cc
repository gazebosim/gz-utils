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

#include <ignition/utils/Environment.hh>

/////////////////////////////////////////////////
bool ignition::utils::env(const std::string &_name,
                          std::string &_value,
                          bool _allowEmpty)
{
  std::string v;
  bool valid = false;
#ifdef _WIN32
  const DWORD buffSize = 32767;
  static char buffer[buffSize];
  if (GetEnvironmentVariable(_name.c_str(), buffer, buffSize))
  {
    v = buffer;
  }

  if (!v.empty())
  {
    valid = true;
  }

  if (_allowEmpty)
  {
    // Reading environment variable with _allowEmpty is unsupported on Windows
    return false;
  }

#else
  const char *cvar = std::getenv(_name.c_str());
  if (cvar != nullptr)
  {
    v = cvar;
    valid = true;

    if (v[0] == '\0' && !_allowEmpty)
    {
      valid = false;
    }
  }
#endif
  if (valid)
  {
    _value = v;
    return true;
  }
  return false;
}

/////////////////////////////////////////////////
bool ignition::utils::setenv(const std::string &_name,
                             const std::string &_value)
{
#ifdef _WIN32
  if (0 != _putenv_s(_name.c_str(), _value.c_str()))
  {
    return false;
  }
#else
  if (0 != ::setenv(_name.c_str(), _value.c_str(), true))
  {
    return false;
  }
#endif
  return true;
}

/////////////////////////////////////////////////
bool ignition::utils::unsetenv(const std::string &_name)
{
#ifdef _WIN32
  if (0 != _putenv_s(_name.c_str(), ""))
  {
    return false;
  }
#else
  if (0 != ::unsetenv(_name.c_str()))
  {
    return false;
  }
#endif
  return true;
}

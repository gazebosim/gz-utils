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

#include <gz/utils/Environment.hh>

#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

extern char ** environ;

namespace gz
{
namespace utils
{
inline namespace GZ_UTILS_VERSION_NAMESPACE {

/////////////////////////////////////////////////
bool env(const std::string &_name, std::string &_value, bool _allowEmpty)
{
#ifdef _WIN32
  size_t requiredSize;
  getenv_s(&requiredSize, NULL, 0, _name.c_str());
  if (requiredSize == 0)
  {
    return false;
  }

  char* env_value = new char[requiredSize];
  getenv_s(&requiredSize, env_value, requiredSize, _name.c_str());
  _value = std::string(env_value);
  delete[] env_value;
  return true;
#else
  bool valid = false;
  std::string v;
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
  if (valid)
  {
    _value = v;
    return true;
  }
  return false;
#endif
}

/////////////////////////////////////////////////
bool setenv(const std::string &_name, const std::string &_value)
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
bool unsetenv(const std::string &_name)
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

/////////////////////////////////////////////////
bool clearenv()
{
  bool success = true;
#if __linux__
  if (0 != ::clearenv())
  {
    success = false;
  }
#else
  // Windows and macOS don't have clearenv
  // so iterate and clear one-by-one
  for (const auto &[key, value] : env())
  {
    success &= unsetenv(key);
  }
#endif
  return success;

}

/////////////////////////////////////////////////
EnvironmentMap env()
{
  EnvironmentMap ret;
#ifdef _WIN32
  DWORD environment_block_size = GetEnvironmentBlockSize();

  // Allocate a buffer to store the environment block.
  LPCH env_buf = (LPCH)malloc(environment_block_size);
  if (env_buf == nullptr) {
    return {};
  }
  // Get the environment block.
  if (!GetEnvironmentVariables(env_buf, environment_block_size)) {
    free(env_buf);
    return {};
  }
  // Parse the environment block into an unordered_map.
  LPCH env_var = env_buf;
  while (*env_var != '\0') {
    // Split the environment variable into a key-value pair.
    char* equal_sign = strchr(env_var, '=');
    if (equal_sign == nullptr) {
      continue;
    }

    // Get the key and value of the environment variable.
    std::string key(env_var, equal_sign - env_var);
    std::string value(equal_sign + 1);

    // Add the key-value pair to the unordered_map.
    ret[key] = value;

    // Advance to the next environment variable.
    env_var = equal_sign + 1;
  }
  free(env_buf);
#else
  char **currentEnv = environ;
  // In the case that clearenv() was just called
  // currentEnv will be nullptr
  if (currentEnv == nullptr)
    return {};

  for (; *currentEnv; ++currentEnv)
  {
    std::string var(*currentEnv);
    auto key = var.substr(0, var.find('='));
    var.erase(0, var.find('=') + 1);
    ret[key] = var;
  }
#endif
  return ret;
}

/////////////////////////////////////////////////
bool setenv(const EnvironmentMap &_vars)
{
  bool success = true;
  for (const auto &[key, value] : _vars)
  {
    success &= setenv(key, value);
  }
  return success;
}

/////////////////////////////////////////////////
std::string printenv()
{
  std::string ret;
  // Variables are in an unordered_map as we generally don't
  // care, but for printing sort for consistent display
  auto currentEnv = env();
  auto sorted = std::vector<std::pair<std::string, std::string>>(
    currentEnv.begin(), currentEnv.end());
  std::sort(sorted.begin(), sorted.end());
  for (const auto &[key, value] : sorted)
  {
    ret.append(key);
    ret.append("=");
    ret.append(value);
    ret.append("\n");
  }
  return ret;
}
}  // namespace GZ_UTILS_VERSION_NAMESPACE
}  // namespace utils
}  // namespace gz

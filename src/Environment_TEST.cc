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

#include <gtest/gtest.h>

#include <gz/utils/Environment.hh>

using namespace ignition;

/////////////////////////////////////////////////
TEST(Environment, emptyENV)
{
  std::string var;
  EXPECT_FALSE(utils::env("!!SHOULD_NOT_EXIST!!", var));
  EXPECT_TRUE(var.empty());
}

/////////////////////////////////////////////////
TEST(Environment, envSet)
{
  const auto key = "IGN_ENV_SET";
  ASSERT_TRUE(utils::setenv(key, "VALUE"));

  // Check set var
  {
    std::string value;
    EXPECT_TRUE(utils::env(key, value));
    EXPECT_FALSE(value.empty());
    EXPECT_EQ("VALUE", value);
  }

  // Check set var with allowEmpty
  {
    std::string value;
    EXPECT_TRUE(utils::env(key, value, true));
    EXPECT_FALSE(value.empty());
    EXPECT_EQ("VALUE", value);
  }

  // Check set var without allowEmpty
  {
    std::string value;
    EXPECT_TRUE(utils::env(key, value, false));
    EXPECT_FALSE(value.empty());
    EXPECT_EQ("VALUE", value);
  }

  ASSERT_TRUE(utils::unsetenv(key));
}

/////////////////////////////////////////////////
TEST(Environment, envUnset)
{
  const auto key = "IGN_ENV_UNSET";
  ASSERT_TRUE(utils::unsetenv(key));

  // Check unset var (default)
  {
    std::string value;
    EXPECT_FALSE(utils::env(key, value));
    EXPECT_TRUE(value.empty());
  }

  // Check unset var with allowEmpty
  {
    std::string value;
    EXPECT_FALSE(utils::env(key, value, true));
    EXPECT_TRUE(value.empty());
  }

  // Check unset var without allowEmpty
  {
    std::string value;
    EXPECT_FALSE(utils::env(key, value, false));
    EXPECT_TRUE(value.empty());
  }
  ASSERT_TRUE(utils::unsetenv(key));
}

/////////////////////////////////////////////////
TEST(Util_TEST, envSetEmpty)
{
  const auto key = "IGN_ENV_SET_EMPTY";

  ASSERT_TRUE(utils::setenv(key, ""));
  ASSERT_FALSE(utils::setenv("", ""));

  // Check set empty var (default)
  {
    std::string value;
    EXPECT_FALSE(utils::env(key, value));
    EXPECT_TRUE(value.empty());
  }

#ifdef _WIN32
  {
    // This will warn on Windows, but return false
    std::string value;
    EXPECT_FALSE(utils::env(key, value, true));
    EXPECT_TRUE(value.empty());
  }
#else
  {
    // This will not warn and return true on Linux,
    // as empty environment variables are allowed.
    std::string value;
    EXPECT_TRUE(utils::env(key, value, true));
    EXPECT_TRUE(value.empty());
  }
#endif

  // Check set empty var without allowEmpty
  {
    std::string value;
    EXPECT_FALSE(utils::env(key, value, false));
    EXPECT_TRUE(value.empty());
  }
  ASSERT_TRUE(utils::unsetenv(key));
}

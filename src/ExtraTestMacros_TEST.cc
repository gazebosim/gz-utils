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

#include <gz/utils/ExtraTestMacros.hh>

GTEST_TEST(ExtraTestMacros, GZ_UTILS_TEST_ENABLED_ONLY_ON_WIN32(OnlyWindowsOn))
{
  ASSERT_TRUE(true);
}

GTEST_TEST(ExtraTestMacros, GZ_UTILS_TEST_DISABLED_ON_WIN32(OnlyWindowsOff))
{
  ASSERT_TRUE(true);
}

GTEST_TEST(ExtraTestMacros, GZ_UTILS_TEST_ENABLED_ONLY_ON_MAC(OnlyMacOn))
{
  ASSERT_TRUE(true);
}

GTEST_TEST(ExtraTestMacros, GZ_UTILS_TEST_DISABLED_ON_MAC(OnlyMacOff))
{
  ASSERT_TRUE(true);
}

GTEST_TEST(ExtraTestMacros, GZ_UTILS_TEST_ENABLED_ONLY_ON_LINUX(OnlyLinuxOn))
{
  ASSERT_TRUE(true);
}

GTEST_TEST(ExtraTestMacros, GZ_UTILS_TEST_DISABLED_ON_LINUX(OnlyLinuxOff))
{
  ASSERT_TRUE(true);
}

GTEST_TEST(ExtraTestMacros, GZ_UTILS_TEST_ENABLED_ONLY_ON_ARM32(OnlyArm32On))
{
  ASSERT_TRUE(true);
}

GTEST_TEST(ExtraTestMacros, GZ_UTILS_TEST_DISABLED_ON_ARM32(OnlyArm32Off))
{
  ASSERT_TRUE(true);
}

GTEST_TEST(ExtraTestMacros, GZ_UTILS_TEST_ENABLED_ONLY_ON_ARM64(OnlyArm64On))
{
  ASSERT_TRUE(true);
}

GTEST_TEST(ExtraTestMacros, GZ_UTILS_TEST_DISABLED_ON_ARM64(OnlyArm64Off))
{
  ASSERT_TRUE(true);
}

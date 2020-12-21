/*
 * Copyright (C) 2020 Open Source Robotics Foundation
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

#include "TestClass.hh"

#include <gtest/gtest.h>

//////////////////////////////////////////////////
TEST(ImplPtr, TestClass)
{
  TestClass test("Hello World");
  EXPECT_EQ("Hello World", test.GetTestText());

  TestClass copy{test};
  EXPECT_EQ("Hello World", copy.GetTestText());

  TestClass moved = std::move(test);
  EXPECT_EQ("Hello World", moved.GetTestText());

  EXPECT_EQ(nullptr, test.dataPtr);
  EXPECT_NE(nullptr, copy.dataPtr);
  EXPECT_NE(nullptr, moved.dataPtr);
}

//////////////////////////////////////////////////
TEST(ImplPtr, TestClassUnique)
{
  TestClassUnique test("Hello World");
  EXPECT_EQ("Hello World", test.GetTestText());

  // This is not possible to compile, as copy
  // and assignment operators are deleted
  // TestClassUnique copy{test};
  // EXPECT_EQ("Hello World", copy.GetTestText());

  TestClassUnique moved = std::move(test);
  EXPECT_EQ("Hello World", moved.GetTestText());

  EXPECT_EQ(nullptr, test.dataPtr);
  EXPECT_NE(nullptr, moved.dataPtr);
}

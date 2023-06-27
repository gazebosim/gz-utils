/*
 * Copyright (C) 2022 Open Source Robotics Foundation
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

#include <gz/utils/Subprocess.hh>

#include <chrono>
#include <thread>

using Subprocess = gz::utils::Subprocess;

static constexpr const char * kExecutablePath = SUBPROCESS_EXECUTABLE_PATH;

/////////////////////////////////////////////////
TEST(Subprocess, CreateInvalid)
{
  auto proc = Subprocess({"an_executable_that_will_never_exist"});
  EXPECT_FALSE(proc.Alive());
}

/////////////////////////////////////////////////
TEST(Subprocess, CreateValid)
{
  auto proc = Subprocess({kExecutablePath, "--help"});

  // Sleep for just a bit to guarantee executable finishes
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_FALSE(proc.Alive());

  auto cout = proc.Stdout();
  auto cerr = proc.Stdout();

  EXPECT_FALSE(cout.empty());
  EXPECT_TRUE(cerr.empty());

  auto ret = proc.Join();
  EXPECT_EQ(0u, ret);
}

/////////////////////////////////////////////////
TEST(Subprocess, Cout)
{
  auto proc = Subprocess({kExecutablePath,
                          "--output=cout",
                          "--iterations=10",
                          "--iteration-ms=10"});

  // Sleep for just a bit to guarantee executable finishes
  EXPECT_TRUE(proc.Alive());

  // Block until the executable is done
  auto ret = proc.Join();
  EXPECT_EQ(0u, ret);

  auto cout = proc.Stdout();
  auto cerr = proc.Stderr();
  EXPECT_FALSE(cout.empty());
  EXPECT_TRUE(cerr.empty());
}

/////////////////////////////////////////////////
TEST(Subprocess, Cerr)
{
  auto proc = Subprocess({kExecutablePath,
                          "--output=cerr",
                          "--iterations=10",
                          "--iteration-ms=10"});
  EXPECT_TRUE(proc.Alive());

  // Block until the executable is done
  auto ret = proc.Join();
  EXPECT_EQ(0u, ret);

  EXPECT_FALSE(proc.Alive());
  auto cout = proc.Stdout();
  auto cerr = proc.Stderr();
  EXPECT_TRUE(cout.empty());
  EXPECT_FALSE(cerr.empty());
}

/////////////////////////////////////////////////
TEST(Subprocess, Environment)
{
  {
    auto proc = Subprocess({kExecutablePath, "--output=cout"},
                           {"ENV_VAR=foobar"});
    // Block until the executable is done
    auto ret = proc.Join();
    EXPECT_EQ(0u, ret);

    auto cout = proc.Stdout();
    EXPECT_NE(std::string::npos, cout.find("ENV_VAR=foobar"));
  }

  {
    auto proc = Subprocess({kExecutablePath, "--output=cerr"},
                           {"ENV_VAR=foobar2"});
    // Block until the executable is done
    auto ret = proc.Join();
    EXPECT_EQ(0u, ret);

    auto cerr = proc.Stderr();
    EXPECT_NE(std::string::npos, cerr.find("ENV_VAR=foobar2"));
  }

  {
    auto proc = Subprocess({kExecutablePath},
                           {"ENV_VAR=foobar3"});
    // Block until the executable is done
    auto ret = proc.Join();
    EXPECT_EQ(0u, ret);

    auto cout = proc.Stdout();
    auto cerr = proc.Stderr();
    EXPECT_EQ(std::string::npos, cerr.find("ENV_VAR=foobar3"));
    EXPECT_EQ(std::string::npos, cout.find("ENV_VAR=foobar3"));
  }
}

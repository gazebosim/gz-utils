/*
 * Copyright (C) 2023 Open Source Robotics Foundation
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

#include <iostream>
#include <string>
#include <thread>

#include <gz/utils/Environment.hh>
#include <gz/utils/cli/CLI.hpp>

class OutputSink
{
  public: OutputSink(const std::string &_dest):
    dest(_dest)
  {
  }

  public: void Write(const std::string& val)
  {
    if (dest == "cout" || dest == "both")
    {
      std::cout << val << std::endl;

    }
    else if (dest == "cerr" || dest == "both")
    {
      std::cerr << val << std::endl;
    }
    return;
  }

  private: std::string dest;
};

//////////////////////////////////////////////////
int main(int argc, char **argv)
{
  CLI::App app("Subprocess test app");

  std::string output;
  app.add_option("--output", output, "output destination");

  int iters = 0;
  app.add_option("--iterations", iters, "number of iterations to run");

  int iter_ms = 0;
  app.add_option("--iteration-ms", iter_ms, "length of one iteration");

  CLI11_PARSE(app, argc, argv);

  auto sink = OutputSink(output);
  for (int ii = 0; ii < iters; ++ii)
  {
    sink.Write("Iteration: " + std::to_string(ii));
    std::this_thread::sleep_for(std::chrono::milliseconds(iter_ms));
  }

  std::string env_var;
  if(gz::utils::env("ENV_VAR", env_var))
  {
    sink.Write("ENV_VAR=" + env_var);
  }
  return 0;
}

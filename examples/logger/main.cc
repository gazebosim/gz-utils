/*
 * Copyright (C) 2024 Open Source Robotics Foundation
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

#include <gz/utils/logger/Console.hh>
#include <gz/utils/logger/SplitSink.hh>
#include <gz/utils/config.hh>

/*
 * At this point, all logger functionality will be available.
 */

//////////////////////////////////////////////////
int main(int argc, char** argv)
{
  auto splitSink =
    std::make_shared<gz::utils::logger::SplitRingBufferSinkMt<100>>();
  auto splitSinkConsole =
    std::make_shared<gz::utils::logger::SplitConsoleSinkMt>();

  spdlog::logger logger("split_sink", {splitSink, splitSinkConsole});
  logger.set_level(spdlog::level::trace);

  logger.trace("trace");
  logger.debug("debug");
  logger.info("info");
  logger.warn("warn");
  logger.error("error");
  logger.critical("critical");
}

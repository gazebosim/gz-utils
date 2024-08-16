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

#include <gtest/gtest.h>

#include <spdlog/logger.h>
#include <gz/utils/log/SplitSink.hh>

/////////////////////////////////////////////////
TEST(SplitConsoleSink, foo)
{
  auto splitSink = std::make_shared<gz::utils::log::SplitConsoleSinkMt>();

  spdlog::logger logger("split_sink", {splitSink});
  logger.set_level(spdlog::level::trace);

  logger.trace("trace");
  logger.debug("debug");
  logger.info("info");
  logger.warn("warn");
  logger.error("error");
  logger.critical("critical");
}

/////////////////////////////////////////////////
TEST(SplitRingBufferSink, foo)
{
  auto splitSink =
    std::make_shared<gz::utils::log::SplitRingBufferSinkMt<100>>();
  auto splitSinkConsole =
    std::make_shared<gz::utils::log::SplitConsoleSinkMt>();

  spdlog::logger logger("split_sink", {splitSink, splitSinkConsole});
  logger.set_level(spdlog::level::trace);

  logger.trace("trace");
  logger.debug("debug");
  logger.info("info");
  logger.warn("warn");
  logger.error("error");
  logger.critical("critical");

  {
    auto logs = splitSink->last_raw_stdout();
    EXPECT_EQ(logs[0].payload, "trace");
    EXPECT_EQ(logs[1].payload, "debug");
    EXPECT_EQ(logs[2].payload, "info");
  }

  {
    auto logs = splitSink->last_raw_stderr();
    EXPECT_EQ(logs[0].payload, "warn");
    EXPECT_EQ(logs[1].payload, "error");
    EXPECT_EQ(logs[2].payload, "critical");
  }
}
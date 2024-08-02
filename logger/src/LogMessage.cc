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

#include <spdlog/spdlog.h>
#include <gz/utils/logger/LogMessage.hh>

namespace gz::utils::logger
{
/////////////////////////////////////////////////
LogMessage::LogMessage(spdlog::level::level_enum _logLevel,
                      const char *_logger,
                      const char *_file,
                      int _line):
  severity(_logLevel),
  logger(_logger == nullptr ? spdlog::default_logger() : spdlog::get(_logger)),
  sourceLocation(_file, _line, "")
{
}

/////////////////////////////////////////////////
LogMessage::~LogMessage()
{
  if (sourceLocation.filename != nullptr)
  {
    logger->log(this->sourceLocation, this->severity, this->ss.str());
  } else {
    logger->log(this->severity, this->ss.str());
  }
}
/////////////////////////////////////////////////
std::ostream &LogMessage::stream()
{
  return this->ss;
}

}  // namespace gz::utils::logger

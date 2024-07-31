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

#ifndef GZ_UTILS_LOGGER_LOGMESSAGE_HH_
#define GZ_UTILS_LOGGER_LOGMESSAGE_HH_

#include <spdlog/spdlog.h>

#include <iosfwd>
#include <sstream>

namespace gz::utils::logger
{

class LogMessage
{
  /// \brief Constructor.
  /// \param[in] _logLevel Log level.
  public: explicit LogMessage(spdlog::level::level_enum _logLevel,
                      const char *_logger = nullptr,
                      const char *_file = nullptr,
                      int _line = -1);

  /// \brief Destructor.
  public: ~LogMessage();

  /// \brief Get access to the underlying stream.
  /// \return The underlying stream.
  public: std::ostream &stream();

  /// \brief Log level.
  private: spdlog::level::level_enum severity;

  private: std::shared_ptr<spdlog::logger> logger;

  /// \brief Source file location information.
  private: spdlog::source_loc sourceLocation;

  /// \brief Underlying stream.
  private: std::ostringstream ss;
};
}  // namespace gz::utils::logger

#endif  // GZ_UTILS_LOGGER_LOGMESSAGE_HH_

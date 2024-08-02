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
#ifndef GZ_UTILS_CONSOLE_HH_
#define GZ_UTILS_CONSOLE_HH_

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include <gz/utils/ImplPtr.hh>
#include <gz/utils/SuppressWarning.hh>

#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

namespace gz::utils::logger
{
  /// \brief Gazebo console and file logging class.
  /// This will configure spdlog with a sane set of defaults for logging to the
  /// console as well as a file.
  class GZ_UTILS_VISIBLE Console
  {
    /// \brief Class constructor.
    /// \param[in] _loggerName Logger name.
    public: explicit Console(const std::string &_loggerName);

    /// \brief Set the console output color mode.
    ///\param[in] _mode Color mode.  
    public: void SetColorMode(spdlog::color_mode _mode);

    /// \brief Set the log destination filename.
    /// \param[in] _filename Log file name.
    public: void SetLogDestination(const std::string &_filename);

    /// \brief Get the log destination filename.
    /// \return Log file name.
    public: std::string LogDestination() const;

    /// \brief Access the underlying spdlog logger.
    /// \return The spdlog logger.
    public: [[nodiscard]] spdlog::logger &Logger() const;

    /// \brief Access the underlying spdlog logger, with ownership.
    /// \return The spdlog logger.
    public: [[nodiscard]] std::shared_ptr<spdlog::logger> LoggerPtr() const;

    /// \brief Access the global gz console logger.
    /// \return The gz consoler logger.
    public: static Console &Root();

    /// \brief Implementation Pointer.
    GZ_UTILS_UNIQUE_IMPL_PTR(dataPtr)
  };
}

#endif  // GZ_UTILS_CONSOLE_HH_

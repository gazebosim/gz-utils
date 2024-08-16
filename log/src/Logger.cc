/*
 * Copyright (C) 2024 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <memory>
#include <string>

#include <gz/utils/log/Logger.hh>
#include <gz/utils/log/SplitSink.hh>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/dist_sink.h>
#include <spdlog/spdlog.h>

namespace gz::utils::log
{
/// \brief Private data for the Logger class.
class Logger::Implementation
{
  /// \brief Constructor.
  /// \param[in] _loggerName Logger name.
  public: explicit Implementation(const std::string &_loggerName)
    : consoleSink(std::make_shared<SplitConsoleSinkMt>()),
      sinks(std::make_shared<spdlog::sinks::dist_sink_mt>()),
      logger(std::make_shared<spdlog::logger>(_loggerName, sinks))
  {
  }

  /// \brief The console sink with stdout and stderr.
  std::shared_ptr<SplitConsoleSinkMt> consoleSink;

  /// \brief The file sink for logging into a file.
  std::shared_ptr<spdlog::sinks::basic_file_sink_mt> fileSink {nullptr};

  /// \brief A sink distribution storing multiple sinks.
  std::shared_ptr<spdlog::sinks::dist_sink_mt> sinks {nullptr};

  /// \brief The underlying spdlog logger.
  std::shared_ptr<spdlog::logger> logger {nullptr};
};

/////////////////////////////////////////////////
Logger::Logger(const std::string &_loggerName)
  : dataPtr(gz::utils::MakeUniqueImpl<Implementation>(_loggerName))
{
  // Add the console sink by default.
  this->dataPtr->sinks->add_sink(this->dataPtr->consoleSink);

  // Configure the logger.
  this->dataPtr->logger->set_level(spdlog::level::err);
  this->dataPtr->logger->flush_on(spdlog::level::err);

  spdlog::flush_every(std::chrono::seconds(5));
  spdlog::register_logger(this->dataPtr->logger);
}

/////////////////////////////////////////////////
void Logger::SetLogDestination(const std::string &_filename)
{
  if (this->dataPtr->fileSink)
    this->dataPtr->sinks->remove_sink(this->dataPtr->fileSink);

  if (!_filename.empty())
  {
    this->dataPtr->fileSink =
      std::make_shared<spdlog::sinks::basic_file_sink_mt>(_filename, true);
    this->dataPtr->sinks->add_sink(this->dataPtr->fileSink);
  }
}

/////////////////////////////////////////////////
std::string Logger::LogDestination() const
{
  std::string logPath = "";
  if (this->dataPtr->fileSink)
    logPath = this->dataPtr->fileSink->filename();

  return logPath;
}

/////////////////////////////////////////////////
spdlog::logger &Logger::RawLogger() const
{
  return *this->dataPtr->logger;
}

/////////////////////////////////////////////////
std::shared_ptr<spdlog::logger> Logger::RawLoggerPtr() const
{
  return this->dataPtr->logger;
}

}  // namespace gz::utils::log

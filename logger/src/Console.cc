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
#include <sstream>
#include <string>

#include <gz/utils/logger/Console.hh>
#include <gz/utils/NeverDestroyed.hh>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/dist_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace {
/// \brief Custom log sink that routes to stdout/stderr in Gazebo conventions.
class GzSplitSink : public spdlog::sinks::sink
{
  /// \brief Class destructor.
  public: ~GzSplitSink() override = default;

  /// \brief Log a message.
  /// \param[in] _msg The message to log.
  public: void log(const spdlog::details::log_msg &_msg) override
  {
    if (_msg.level == spdlog::level::warn       ||
        _msg.level == spdlog::level::err        ||
        _msg.level == spdlog::level::critical)
    {
      this->stderr.log(_msg);
    }
    else
      this->stdout.log(_msg);
  }

  /// \brief Flush messages.
  public: void flush() override
  {
    this->stdout.flush();
    this->stderr.flush();
  }

  /// \brief Set the logging pattern.
  /// \param[in] _pattern The logging pattern. 
  public: void set_pattern(const std::string &_pattern) override
  {
    this->stdout.set_pattern(_pattern);
    this->stderr.set_pattern(_pattern);
  }

  /// \brief Set the new formatter.
  /// \param[in] _sinkFormatter The formatter.
  public: void set_formatter(std::unique_ptr<spdlog::formatter> _sinkFormatter)
  override
  {
    this->stdout.set_formatter(_sinkFormatter->clone());
    this->stderr.set_formatter(std::move(_sinkFormatter));
  }

  /// \brief Set the color mode.
  /// \param[in] _mode Color mode.
  public: void set_color_mode(spdlog::color_mode _mode)
  {
    this->stdout.set_color_mode(_mode);
    this->stderr.set_color_mode(_mode);
  }

  /// \brief Standard output.
  private: spdlog::sinks::stdout_color_sink_mt stdout;

  /// \brief Standard error.
  private: spdlog::sinks::stderr_color_sink_mt stderr;
};
}  // namespace

namespace gz::utils::logger
{
/// \brief Private data for the Console class.
class Console::Implementation
{
  /// \brief Constructor.
  /// \param[in] _loggerName Logger name.
  public: explicit Implementation(const std::string &_loggerName)
    : consoleSink(std::make_shared<GzSplitSink>()),
      sinks(std::make_shared<spdlog::sinks::dist_sink_mt>()),
      logger(std::make_shared<spdlog::logger>(_loggerName, sinks))
  {
  }

  /// \brief .
  std::shared_ptr<GzSplitSink> consoleSink;

  /// \brief .
  std::shared_ptr<spdlog::sinks::basic_file_sink_mt> fileSink {nullptr};

  /// \brief .
  std::shared_ptr<spdlog::sinks::dist_sink_mt> sinks {nullptr};

  /// \brief .
  std::shared_ptr<spdlog::logger> logger {nullptr};
};

/////////////////////////////////////////////////
Console::Console(const std::string &_loggerName)
  : dataPtr(gz::utils::MakeUniqueImpl<Implementation>(_loggerName))
{
  // Add the console sink as a destination.
  this->dataPtr->sinks->add_sink(this->dataPtr->consoleSink);

  // Configure the logger.
  this->dataPtr->logger->set_level(spdlog::level::err);
  this->dataPtr->logger->flush_on(spdlog::level::err);

  spdlog::flush_every(std::chrono::seconds(5));
  spdlog::register_logger(this->dataPtr->logger);
}

/////////////////////////////////////////////////
void Console::SetColorMode(spdlog::color_mode _mode)
{
  this->dataPtr->consoleSink->set_color_mode(_mode);
}

/////////////////////////////////////////////////
void Console::SetLogDestination(const std::string &_filename)
{
  if (this->dataPtr->fileSink)
    this->dataPtr->sinks->remove_sink(this->dataPtr->fileSink);

  this->dataPtr->fileSink =
    std::make_shared<spdlog::sinks::basic_file_sink_mt>(_filename, true);
  this->dataPtr->sinks->add_sink(this->dataPtr->fileSink);
}

/////////////////////////////////////////////////
std::string Console::LogDestination() const
{
  std::string logPath = "";
  if (this->dataPtr->fileSink)
  {
    logPath = this->dataPtr->fileSink->filename();
  }

  return logPath;
}

/////////////////////////////////////////////////
spdlog::logger &Console::Logger() const
{
  return *this->dataPtr->logger;
}

/////////////////////////////////////////////////
std::shared_ptr<spdlog::logger> Console::LoggerPtr() const
{
  return this->dataPtr->logger;
}

/////////////////////////////////////////////////
Console &Console::Root()
{
  static gz::utils::NeverDestroyed<Console> root{"gz"};
  return root.Access();
}
}  // namespace gz::utils::logger

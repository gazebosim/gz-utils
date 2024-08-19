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

#ifndef GZ_UTILS_LOG_SPLITSINK_HH_
#define GZ_UTILS_LOG_SPLITSINK_HH_

#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include <gz/utils/config.hh>
#include <gz/utils/log/Export.hh>

#include <spdlog/details/log_msg.h>
#include <spdlog/details/null_mutex.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/ringbuffer_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace gz
{
namespace utils
{
namespace log
{
inline namespace GZ_UTILS_LOG_VERSION_NAMESPACE {

/// \brief Logging sink for spdlog that logs in Gazebo-conventions.
///
/// This will route messages with severity (warn, err, critical) to stderr,
/// and all other levels (info, debug, trace) to stdout.
template<typename Mutex>
class SplitConsoleSink : public spdlog::sinks::base_sink<Mutex>
{
  /// \brief Class constructor.
  public: SplitConsoleSink() = default;

  /// \brief No copy constructor.
  public: SplitConsoleSink(const SplitConsoleSink &) = delete;

  /// \brief No asignment operator.
  public: SplitConsoleSink &operator=(const SplitConsoleSink &) = delete;

  /// \brief Try to log a message.
  /// \param[in] _msg The message to log.
  protected: void sink_it_(const spdlog::details::log_msg &_msg) override
  {
    if (!this->should_log(_msg.level))
      return;

    if (_msg.level == spdlog::level::warn      ||
        _msg.level == spdlog::level::err       ||
        _msg.level == spdlog::level::critical)
    {
      this->stderr.log(_msg);
    }
    else
      this->stdout.log(_msg);
  }

  /// \brief Flush messages.
  protected: void flush_() override
  {
    this->stdout.flush();
    this->stderr.flush();
  }

  /// \brief Set the logging pattern.
  /// \param[in] _pattern The logging pattern.
  protected: void set_pattern_(const std::string &_pattern) override
  {
    this->set_formatter(
      spdlog::details::make_unique<spdlog::pattern_formatter>(_pattern));
  }

  /// \brief Set the new formatter.
  /// \param[in] _sinkFormatter The formatter.
  protected: void set_formatter_(
    std::unique_ptr<spdlog::formatter> _sinkFormatter) override
  {
    spdlog::sinks::base_sink<Mutex>::formatter_ = std::move(_sinkFormatter);
    this->stdout.set_formatter(
      spdlog::sinks::base_sink<Mutex>::formatter_->clone());
    this->stderr.set_formatter(
      spdlog::sinks::base_sink<Mutex>::formatter_->clone());
  }

  /// \brief Standard output.
  private: spdlog::sinks::stdout_color_sink_st stdout;

  /// \brief Standard error.
  private: spdlog::sinks::stderr_color_sink_st stderr;
};

using SplitConsoleSinkMt = SplitConsoleSink<std::mutex>;
using SplitConsoleSinkSt = SplitConsoleSink<spdlog::details::null_mutex>;

/// \brief Logging sink for spdlog that logs in Gazebo-conventions
///
/// This will route messages with severity (warn, err, critical) to stderr,
/// and all other levels (info, debug, trace) to stdout
template<typename Mutex, size_t numItems>
class SplitRingBufferSink: public spdlog::sinks::base_sink<Mutex>
{
  /// \brief Class constructor.
  public: SplitRingBufferSink() = default;

  /// \brief No copy constructor.
  public: SplitRingBufferSink(const SplitRingBufferSink &) = delete;

  /// \brief No asignment operator.
  public: SplitRingBufferSink &operator=(const SplitRingBufferSink &) = delete;

  /// \brief ToDo.
  /// \param[in] _lim
  /// \return
  public: std::vector<spdlog::details::log_msg_buffer> last_raw_stdout(
    size_t _lim = 0)
  {
    return this->stdout.last_raw(_lim);
  }

  /// \brief ToDo.
  /// \param[in] _lim
  /// \return
  public: std::vector<spdlog::details::log_msg_buffer> last_raw_stderr(
    size_t _lim = 0)
  {
    return this->stderr.last_raw(_lim);
  }

  /// \brief ToDo.
  /// \param[in] _lim
  /// \return
  public: std::vector<std::string> last_formatted_stdout(size_t _lim = 0)
  {
    return this->stdout.last_formatted(_lim);
  }

  /// \brief ToDo.
  /// \param[in] _lim
  /// \return
  public: std::vector<std::string> last_formatted_stderr(size_t _lim = 0)
  {
    return this->stderr.last_formatted(_lim);
  }

  /// \brief ToDo.
  /// \param[in] _msg ToDo.
  protected: void sink_it_(const spdlog::details::log_msg &_msg) override
  {
    if (!this->should_log(_msg.level))
      return;

    if (_msg.level == spdlog::level::warn      ||
        _msg.level == spdlog::level::err       ||
        _msg.level == spdlog::level::critical)
    {
      this->stderr.log(_msg);
    }
    else
      this->stdout.log(_msg);
  }

  /// \brief Flush messages.
  protected: void flush_() override
  {
    this->stdout.flush();
    this->stderr.flush();
  }

  /// \brief Set the logging pattern.
  /// \param[in] _pattern The logging pattern.
  protected: void set_pattern_(const std::string &_pattern) override
  {
    this->set_formatter_(
      spdlog::details::make_unique<spdlog::pattern_formatter>(_pattern));
  }

  /// \brief Set the new formatter.
  /// \param[in] _sinkFormatter The formatter.
  protected: void set_formatter_(
    std::unique_ptr<spdlog::formatter> _sinkFormatter) override
  {
    spdlog::sinks::base_sink<Mutex>::formatter_ = std::move(_sinkFormatter);
    this->stdout.set_formatter(
      spdlog::sinks::base_sink<Mutex>::formatter_->clone());
    this->stderr.set_formatter(
      spdlog::sinks::base_sink<Mutex>::formatter_->clone());
  }

  /// \brief Standard output.
  private: spdlog::sinks::ringbuffer_sink_st stdout {numItems};

  /// \brief Standard error.
  private: spdlog::sinks::ringbuffer_sink_st stderr {numItems};
};

template <size_t numItems>
using SplitRingBufferSinkMt = SplitRingBufferSink<std::mutex, numItems>;

}  // namespace GZ_UTILS_LOG_VERSION_NAMESPACE
}  // namespace log
}  // namespace utils
}  // namespace gz

#endif  // GZ_UTILS_LOG_SPLITSINK_HH__

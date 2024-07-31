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

#ifndef GZ_UTILS_LOGGER_SPLITSINK_HH_
#define GZ_UTILS_LOGGER_SPLITSINK_HH_

#include <string>

#include <spdlog/details/log_msg.h>
#include <spdlog/details/null_mutex.h>
#include <spdlog/details/console_globals.h>
#include <spdlog/pattern_formatter.h>

#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/ringbuffer_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace gz::utils::logger
{
/// \brief Logging sink for spdlog that logs in Gazebo-conventions
///
/// This will route messages with severity (warn, err, critical) to stderr,
/// and all other levels (info, debug, trace) to stdout
template<typename Mutex>
class SplitConsoleSink : public spdlog::sinks::base_sink<Mutex>
{
  public: SplitConsoleSink() = default;
  public: SplitConsoleSink(const SplitConsoleSink &) = delete;
  public: SplitConsoleSink &operator=(const SplitConsoleSink &) = delete;

  protected: void sink_it_(const spdlog::details::log_msg &_msg) override
  {
    if (!this->should_log(_msg.level))
    {
      return;
    }

    if (_msg.level == spdlog::level::warn       ||
        _msg.level == spdlog::level::err        ||
        _msg.level == spdlog::level::critical)
    {
      this->stderr.log(_msg);
    }
    else
      this->stdout.log(_msg);
  }

  protected: void flush_() override
  {
    this->stdout.flush();
    this->stderr.flush();
  }

  void set_pattern_(const std::string &pattern) override
  {
    this->set_formatter_(spdlog::details::make_unique<spdlog::pattern_formatter>(pattern));
  }

  void set_formatter_(std::unique_ptr<spdlog::formatter> sink_formatter) override
  {
    spdlog::sinks::base_sink<Mutex>::formatter_ = std::move(sink_formatter);
    this->stdout.set_formatter(spdlog::sinks::base_sink<Mutex>::formatter_->clone());
    this->stderr.set_formatter(spdlog::sinks::base_sink<Mutex>::formatter_->clone());
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
template<typename Mutex, size_t n_items>
class SplitRingBufferSink: public spdlog::sinks::base_sink<Mutex>
{
  public: SplitRingBufferSink() = default;
  public: SplitRingBufferSink(const SplitRingBufferSink &) = delete;
  public: SplitRingBufferSink &operator=(const SplitRingBufferSink &) = delete;

  public: std::vector<spdlog::details::log_msg_buffer> last_raw_stdout(size_t lim = 0)
  {
    return this->stdout.last_raw(lim);
  }

  public: std::vector<spdlog::details::log_msg_buffer> last_raw_stderr(size_t lim = 0)
  {
    return this->stderr.last_raw(lim);
  }

  public: std::vector<std::string> last_formatted_stdout(size_t lim = 0)
  {
    return this->stdout.last_formatted(lim);
  }

  public: std::vector<std::string> last_formatted_stderr(size_t lim = 0)
  {
    return this->stderr.last_formatted(lim);
  }

  protected: void sink_it_(const spdlog::details::log_msg &_msg) override
  {
    if (!this->should_log(_msg.level))
    {
      return;
    }

    if (_msg.level == spdlog::level::warn       ||
        _msg.level == spdlog::level::err        ||
        _msg.level == spdlog::level::critical)
    {
      this->stderr.log(_msg);
    }
    else
      this->stdout.log(_msg);
  }

  protected: void flush_() override
  {
    this->stdout.flush();
    this->stderr.flush();
  }

  protected: void set_pattern_(const std::string &pattern) override
  {
    this->set_formatter_(spdlog::details::make_unique<spdlog::pattern_formatter>(pattern));
  }

  protected: void set_formatter_(std::unique_ptr<spdlog::formatter> sink_formatter) override
  {
    spdlog::sinks::base_sink<Mutex>::formatter_ = std::move(sink_formatter);
    this->stdout.set_formatter(spdlog::sinks::base_sink<Mutex>::formatter_->clone());
    this->stderr.set_formatter(spdlog::sinks::base_sink<Mutex>::formatter_->clone());
  }


  /// \brief Standard output.
  private: spdlog::sinks::ringbuffer_sink_st stdout {n_items};

  /// \brief Standard error.
  private: spdlog::sinks::ringbuffer_sink_st stderr {n_items};
};

template <size_t n_items>
using SplitRingBufferSinkMt = SplitRingBufferSink<std::mutex, n_items>;

}  // namespace gz::utils::logger
#endif  // GZ_UTILS_LOGGER_SPLITSINK_HH__

/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file logger.hpp
 * @version 1.0
 * @date 08/03/2024
 * @brief Logger
 *
 * Logger class
 */

#pragma once


#define QUILL_DISABLE_NON_PREFIXED_MACROS

#include <quill/Backend.h>
#include <quill/Frontend.h>
#include <quill/LogMacros.h>
#include <quill/sinks/ConsoleSink.h>
#include <quill/sinks/FileSink.h>

namespace rflect3d {
//
// class ImGuiSink : public quill::Sink {
// public:
//   void write_log(
//       quill::MacroMetadata const* /** log_metadata **/, uint64_t /** log_timestamp **/,
//       std::string_view /** thread_id **/, std::string_view /** thread_name **/, std::string const& /** process_id
//       **/, std::string_view /** logger_name **/, quill::LogLevel /** log_level **/, std::string_view /**
//       log_level_description **/, std::string_view /** log_level_short_code **/, std::vector<std::pair<
//           std::string,
//           std::string>> const* /** named_args - only populated when named args in the format placeholder are used
//           **/,
//       std::string_view /** log_message **/, std::string_view log_statement
//   ) override {
//     std::lock_guard lock(_mutex);
//     std::ostringstream oss;
//     quill::detail::default_formatter(event, oss);
//     _buffer += oss.str();
//     _buffer += '\n';
//   }
//
//   std::string const& get_buffer() const { return _buffer; }
//  void clear() {
//     std:: std::lock_guard lock(_mutex);
//     _buffer.clear();
//   }
//
// private:
//   std::string _buffer;
//   mutable std::mutex _mutex;
// };

class Logger {
public:
  explicit Logger(std::string const& name) {
    quill::Backend::start();
    auto console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>(std::format("{}_console", name));
    auto file_sink    = quill::Frontend::create_or_get_sink<quill::FileSink>(
        std::format("{}.log", name),
        [] {
          quill::FileSinkConfig cfg;
          cfg.set_open_mode('w');
          cfg.set_filename_append_option(quill::FilenameAppendOption::StartDateTime);
          return cfg;
        }(),
        quill::FileEventNotifier {}
    );
    impl = quill::Frontend::create_or_get_logger(name, {std::move(file_sink), std::move(console_sink)});
  }

  template<typename... Args>
  void info(std::string const& str, Args... args) {
    QUILL_LOG_INFO(impl, str.c_str(), args...);
  }

  template<typename... Args>
  void warning(std::string const& str, Args... args) {
    QUILL_LOG_WARNING(impl, str.c_str(), args...);
  }

  template<typename... Args>
  void error(std::string const& str, Args... args) {
    QUILL_LOG_ERROR(impl, str.c_str(), args...);
  }

private:
  quill::Logger* impl {};
};

class GlobalLogger {
  GlobalLogger()  = default;
  ~GlobalLogger() = default;

public:
  explicit GlobalLogger(GlobalLogger const&)   = delete;
  GlobalLogger& operator=(GlobalLogger const&) = delete;

  static Logger& instance() {
    static Logger log {"Rflect3d"};
    return log;
  }
};

#define LOG_INFO(fmt, ...) rflect3d::GlobalLogger::instance().info(fmt, ##__VA_ARGS__);
#define LOG_WARNING(fmt, ...) rflect3d::GlobalLogger::instance().warning(fmt, ##__VA_ARGS__);
#define LOG_ERROR(fmt, ...) rflect3d::GlobalLogger::instance().error(fmt, ##__VA_ARGS__);

} // namespace rflect3d

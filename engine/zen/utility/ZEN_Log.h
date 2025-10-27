#pragma once

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Zen {
  // spdlog wrapper
  class Log {
  public:
    static void init();

    template <typename... Args> static void trace(fmt::format_string<Args...> fmt, Args &&...args) {
      spdlog::trace(fmt, std::forward<Args>(args)...);
      // SPDLOG_TRACE(std::forward<Args>(args)...);
    }

    template <typename... Args> static void debug(fmt::format_string<Args...> fmt, Args &&...args) {
      spdlog::debug(fmt, std::forward<Args>(args)...);
      // SPDLOG_DEBUG(std::forward<Args>(args)...);
    }

    template <typename... Args> static void info(fmt::format_string<Args...> fmt, Args &&...args) {
      spdlog::info(fmt, std::forward<Args>(args)...);
      // SPDLOG_INFO(std::forward<Args>(args)...);
    }

    template <typename... Args> static void warn(fmt::format_string<Args...> fmt, Args &&...args) {
      spdlog::warn(fmt, std::forward<Args>(args)...);
      // SPDLOG_WARN(std::forward<Args>(args)...);
    }

    template <typename... Args> static void error(fmt::format_string<Args...> fmt, Args &&...args) {
      spdlog::error(fmt, std::forward<Args>(args)...);
      // SPDLOG_ERROR(std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void critical(fmt::format_string<Args...> fmt, Args &&...args) {
      spdlog::critical(fmt, std::forward<Args>(args)...);
      // SPDLOG_CRITICAL(std::forward<Args>(args)...);
    }
  };

}; // namespace Zen

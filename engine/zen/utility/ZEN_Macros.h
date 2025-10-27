#pragma once

#ifdef __ZEN_BUILD_PROFILE_DEBUG
  #include <zen/utility/ZEN_Log.h>
  #include <zen/utility/ZEN_Profiler.h>

  #define ZEN_START_PROFILE_SESSION(name, filePath)    \
    Zen::Profiler::get().startSession(name, filePath);
  #define ZEN_END_PROFILE_SESSION() Zen::Profiler::get().endSession();
  #define ZEN_PROFILE_SCOPE(name) Zen::ProfilerTimer timer##__LINE__(name)
  #define ZEN_PROFILE_FUNCTION() ZEN_PROFILE_SCOPE(__FUNCTION__)

  #define ZEN_LOG_TRACE(...) Zen::Log::trace(__VA_ARGS__)       // spdlog::trace(fmt)
  #define ZEN_LOG_DEBUG(...) Zen::Log::debug(__VA_ARGS__)       // spdlog::debug(fmt)
  #define ZEN_LOG_INFO(...) Zen::Log::info(__VA_ARGS__)         // spdlog::info(fmt)
  #define ZEN_LOG_WARN(...) Zen::Log::warn(__VA_ARGS__)         // spdlog::warn(fmt)
  #define ZEN_LOG_ERROR(...) Zen::Log::error(__VA_ARGS__)       // spdlog::error(__VA_ARGS__)
  #define ZEN_LOG_CRITICAL(...) Zen::Log::critical(__VA_ARGS__) // spdlog::critical(fmt)
  #define ZEN_ASSERT_LOG(cond, msg, ...)                                                 \
    do {                                                                                 \
      if (!(cond)) {                                                                     \
        LOG_CRITICAL("Assertion failed:\n  expr : {}\n  msg  : " msg "\n  loc  : {}:{}", \
                     #cond,                                                              \
                     ##__VA_ARGS__,                                                      \
                     __FILE__,                                                           \
                     __LINE__);                                                          \
        std::abort();                                                                    \
      }                                                                                  \
    } while (0)

#else
  #define ZEN_START_PROFILE_SESSION(name, filePath)
  #define ZEN_END_PROFILE_SESSION()
  #define ZEN_PROFILE_SCOPE(name)
  #define ZEN_PROFILE_FUNCTION()

  #define ZEN_LOG_TRACE(...)
  #define ZEN_LOG_DEBUG(...)
  #define ZEN_LOG_INFO(...)
  #define ZEN_LOG_WARN(...)
  #define ZEN_LOG_ERROR(...)
  #define ZEN_LOG_CRITICAL(...)
  #define ZEN_ASSERT_LOG(cond, msg, ...)
#endif

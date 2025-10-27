#pragma once

#ifdef __ZEN_BUILD_PROFILE_DEBUG
  #include <zen/utility/ZEN_Profiler.h>

  #define ZEN_START_PROFILE_SESSION(name, filePath)    \
    Zen::Profiler::get().startSession(name, filePath);
  #define ZEN_END_PROFILE_SESSION() Zen::Profiler::get().endSession();
  #define ZEN_PROFILE_SCOPE(name) Zen::ProfilerTimer timer##__LINE__(name)
  #define ZEN_PROFILE_FUNCTION() ZEN_PROFILE_SCOPE(__FUNCTION__)
#else
  #define ZEN_START_PROFILE_SESSION(name, filePath)                  \
    ZEN_LOG_TRACE("START PROFILE SESSION FAILED, PROFILING IS OFF!")
  #define ZEN_END_PROFILE_SESSION() ZEN_LOG_TRACE("END PROFILE SESSION FAILED, PROFILING IS OFF!")
  #define ZEN_PROFILE_SCOPE(name)
  #define ZEN_PROFILE_FUNCTION()
#endif

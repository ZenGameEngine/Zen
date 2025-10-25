set(ZEN_UTILITY_HEADER zen/utility/ZEN_Macros.h zen/utility/ZEN_Log.h)
set(ZEN_UTILITY_SRC zen/utility/ZEN_Log.cpp)

if(BUILD_TYPE STREQUAL Debug)
  list(APPEND ZEN_UTILITY_HEADER utility/ZEN_Profiler.h)
endif()

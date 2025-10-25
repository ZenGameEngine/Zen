set(ZEN_UTILITY_HEADERS utility/ZEN_Macros.h)

if(BUILD_TYPE STREQUAL Debug)
  list(APPEND ZEN_UTILITY_HEADERS utility/ZEN_Profiler.h)
endif()

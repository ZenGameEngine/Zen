# Metadata
set(ZEN_ENGINE_VERSION 0.1.0)

project(ZenEngineLib)
include(zen/CMakeLists.txt)
include(zen/core/CMakeLists.txt)
include(zen/textures/CMakeLists.txt)
include(zen/platform/CMakeLists.txt)
include(zen/log/CMakeLists.txt)
include(zen/events/CMakeLists.txt)
include(zen/layer/CMakeLists.txt)
include(zen/renderer/CMakeLists.txt)
include(zen/gui/CMakeLists.txt)
include(zen/inputs/CMakeLists.txt)
include(zen/camera/CMakeLists.txt)
include(zen/particles/CMakeLists.txt)

# System Config
if(UNIX AND NOT APPLE)
  set(ZEN_HEADER
      zen/zen.h
      ${ZEN_BASE_HEADER}
      ${ZEN_CORE_HEADER}
      ${ZEN_TEXTURES_HEADER}
      ${ZEN_LOG_HEADER}
      ${ZEN_LINUX_HEADER}
      ${ZEN_EVENTS_HEADER}
      ${ZEN_LAYER_HEADER}
      ${ZEN_OPENGL_HEADER}
      ${ZEN_RENDERER_HEADER}
      ${ZEN_IMGUI_HEADER}
      ${ZEN_INPUTS_HEADER}
      ${ZEN_CAMERA_HEADER}
      ${ZEN_PARTICLES_HEADER})

  set(ZEN_SRC
      ${ZEN_CORE_SRC}
      ${ZEN_TEXTURES_SRC}
      ${ZEN_LOG_SRC}
      ${ZEN_LINUX_SRC}
      ${ZEN_EVENTS_SRC}
      ${ZEN_LAYER_SRC}
      ${ZEN_OPENGL_SRC}
      ${ZEN_RENDERER_SRC}
      ${ZEN_IMGUI_SRC}
      ${ZEN_INPUTS_SRC}
      ${ZEN_CAMERA_SRC}
      ${ZEN_PARTICLES_SRC})

  list(APPEND ZEN_SRC ${ZEN_HEADER})
  add_library(ZenEngine STATIC ${ZEN_SRC})
  target_compile_definitions(ZenEngine PUBLIC __ZEN_PLATFORM_LINUX)
elseif(WIN32)

  set(ZEN_HEADER
      zen/zen.h
      ${ZEN_BASE_HEADER}
      ${ZEN_CORE_HEADER}
      ${ZEN_TEXTURES_HEADER}
      ${ZEN_LOG_HEADER}
      ${ZEN_LINUX_HEADER}
      ${ZEN_EVENTS_HEADER}
      ${ZEN_LAYER_HEADER}
      ${ZEN_OPENGL_HEADER}
      ${ZEN_RENDERER_HEADER}
      ${ZEN_IMGUI_HEADER}
      ${ZEN_INPUTS_HEADER}
      ${ZEN_CAMERA_HEADER}
      ${ZEN_PARTICLES_HEADER})

  set(ZEN_SRC
      ${ZEN_CORE_SRC}
      ${ZEN_TEXTURES_SRC}
      ${ZEN_LOG_SRC}
      ${ZEN_LINUX_SRC}
      ${ZEN_EVENTS_SRC}
      ${ZEN_LAYER_SRC}
      ${ZEN_OPENGL_SRC}
      ${ZEN_RENDERER_SRC}
      ${ZEN_IMGUI_SRC}
      ${ZEN_INPUTS_SRC}
      ${ZEN_CAMERA_SRC}
      ${ZEN_PARTICLES_SRC})

  list(APPEND ZEN_SRC ${ZEN_HEADER})
  add_library(ZenEngine STATIC ${ZEN_SRC})

  target_compile_definitions(ZenEngine PUBLIC __ZEN_PLATFORM_WINDOWS)
endif()

# Pre-compiled Headers
target_precompile_headers(ZenEngine PRIVATE zen/zen_pch.h)

target_include_directories(
  ZenEngine
  PUBLIC ${ZEN_ROOT_PATH}
  PUBLIC ${ZEN_ROOT_PATH}/engine
  INTERFACE ${ZEN_ROOT_PATH}/engine/zen
  INTERFACE ${ZEN_ROOT_PATH}/engine/zen/core
  INTERFACE ${ZEN_ROOT_PATH}/engine/zen/log
  INTERFACE ${ZEN_ROOT_PATH}/engine/zen/opengl
  INTERFACE ${ZEN_ROOT_PATH}/engine/zen/platform
  INTERFACE ${ZEN_ROOT_PATH}/engine/zen/platform/linux
  INTERFACE ${ZEN_ROOT_PATH}/engine/zen/platform/OpenGL
  INTERFACE ${ZEN_ROOT_PATH}/engine/zen/textures
  INTERFACE ${ZEN_ROOT_PATH}/engine/zen/events
  INTERFACE ${ZEN_ROOT_PATH}/engine/zen/layer
  INTERFACE ${ZEN_ROOT_PATH}/engine/zen/renderer
  INTERFACE ${ZEN_ROOT_PATH}/engine/zen/gui)

include(FetchContent)

cmake_policy(SET CMP0072 NEW)

# OpenGL
find_package(OpenGL REQUIRED)
find_package(glm QUIET CONFIG)

if(NOT TARGET glm)
  FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG a532f5b1cf27d6a3c099437e6959cf7e398a0a67)
endif()

FetchContent_MakeAvailable(glm)

FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG 73db193f853e2ee079bf3ca8a64aa2eaf6459043 # v2.0.8
  GIT_PROGRESS TRUE
  SOURCE_SUBDIR cmake)
FetchContent_MakeAvailable(glad)
glad_add_library(glad_gl_core_46 STATIC REPRODUCIBLE LOADER API gl:core=4.6)

# spdlog

if(NOT TARGET spdlog)
  message(STATUS "spdlog not found, using FetchContent")
  FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.16.0)
  FetchContent_MakeAvailable(spdlog)
endif()

# External libraries
target_link_libraries(
  ZenEngine
  glad_gl_core_46
  glm
  stb_image
  SDL3::SDL3
  spdlog::spdlog
  ${OPENGL_LIBRARIES})

target_link_libraries(ZenEngine ${PLATFORM_LINK_LIBS})

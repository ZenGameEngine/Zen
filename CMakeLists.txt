# Project Setup
cmake_minimum_required(VERSION 3.12..4.1.2)

set(ZEN_VERSION 0.3.0)
set(ZEN_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

project(
  ZEN_CMAKE
  VERSION ${ZEN_VERSION}
  DESCRIPTION "A 2D game engine"
  LANGUAGES CXX)

option(SDL_VENDORED "Use vendored libraries" OFF)
if(SDL_VENDORED)
  add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
  find_package(SDL3 REQUIRED)
endif()

if(WIN32) # Windows
  # System libraries that Windows needs for SDL/OpenGL Required by SDL on
  # MSVC/MinGW
  set(PLATFORM_LIB_DEPS gdi32 user32 opengl32 ws2_32)
  add_compile_definitions(__ZEN_PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE) # Linux
  # System libraries that Linux needs
  set(PLATFORM_LIB_DEPS X11 GL dl pthread)
  add_compile_definitions(__ZEN_PLATFORM_LINUX)
endif()

# C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# ##############################################################################
# DIRECTORIES #
# ##############################################################################
add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(include/stb_image)
add_subdirectory(include/doctest)
add_subdirectory(include/imgui)

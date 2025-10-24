# Project Setup
cmake_minimum_required(VERSION 3.12..4.0.1)
project(
  ZEN_CMAKE
  VERSION 0.1.0
  DESCRIPTION "A 2D game engine"
  LANGUAGES CXX)

set(ZEN_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

option(SDL_VENDORED "Use vendored libraries" OFF)

if(SDL_VENDORED)
  add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
  find_package(SDL3 REQUIRED)
endif()

if(WIN32)
  # Windows build
  add_compile_definitions(__ZEN_PLATFORM_WINDOWS)

  # System libraries that Windows needs for SDL/OpenGL
  set(PLATFORM_LINK_LIBS gdi32 user32 opengl32 ws2_32 # required by SDL on
                                                      # MSVC/MinGW
  )
elseif(UNIX AND NOT APPLE)

  add_compile_definitions(__ZEN_PLATFORM_LINUX)

  # System libraries that Linux needs
  set(PLATFORM_LINK_LIBS X11 GL dl pthread)
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

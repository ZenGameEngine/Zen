#pragma once

// C++
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

// OpenGL
#ifndef __ZEN_OPENGL_H
  #define __ZEN_OPENGL_H
  #include <glad/gl.h>
#endif // !__ZEN_OPENGL_H

// SDL
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_messagebox.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_video.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef __ZEN_BUILD_PROFILE_DEBUG
  // nlohmann/json
  #include <nlohmann/json.hpp>
#endif // !__ZEN_BUILD_PROFILE_DEBUG

// ZEN
#include <zen/utility/ZEN_Log.h>

#pragma once

// C++
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
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

// ZEN
#include <zen/log/ZEN_Log.h>
#pragma once

#include <SDL3/SDL_video.h>
#include <cstdint>
#include <sys/types.h>

namespace Zen {
  typedef struct {
    uint32_t width;
    uint32_t height;
  } Size;
}; // namespace Zen

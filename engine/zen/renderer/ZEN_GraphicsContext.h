#pragma once

#include <zen/zen_pch.h>

namespace Zen {
class GraphicsContext {
  public:
    virtual ~GraphicsContext() = default;

    virtual void init() = 0;
    virtual void swapBuffers() = 0;
    virtual void shutdown() = 0;
    virtual void* nativeContext() const = 0;

    static std::unique_ptr<GraphicsContext> Create(SDL_Window *window);

  private:
};
}; // namespace Zen
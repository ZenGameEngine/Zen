#include <zen/renderer/OpenGL/ZEN_OpenGLContext.h>
#include <zen/renderer/abstractions/ZEN_GraphicsContext.h>

namespace Zen {
  std::unique_ptr<GraphicsContext> GraphicsContext::Create(SDL_Window *window) {
    return std::make_unique<OpenGLContext>(window);
  }
}; // namespace Zen

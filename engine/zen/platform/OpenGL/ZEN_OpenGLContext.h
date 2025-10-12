#pragma once

#include <zen/renderer/ZEN_GraphicsContext.h>
#include <zen/zen_pch.h>

namespace Zen {
  class OpenGLContext : public GraphicsContext {
  public:
    OpenGLContext(SDL_Window *window);
    ~OpenGLContext() override;

    void init() override;
    void swapBuffers() override;

    void shutdown() override;
    void *nativeContext() const override;

  private:
    SDL_Window *m_window      = nullptr;
    SDL_GLContext m_glContext = nullptr;
  };
}; // namespace Zen
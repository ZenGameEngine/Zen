#pragma once

#include <zen/core/ZEN_Core.h>
#include <zen/core/ZEN_Window.h>
#include <zen/renderer/ZEN_Buffer.h>
#include <zen/renderer/ZEN_GraphicsContext.h>
#include <zen/renderer/ZEN_Renderer.h>
#include <zen/renderer/ZEN_Shader.h>
#include <zen/renderer/ZEN_VertexArray.h>
#include <zen/zen_pch.h>

namespace Zen {
  class Application : public EventListener {
  public:
    Application();
    virtual ~Application();

    void run();
    bool onEvent(const SDL_Event &event);

    static Application &get();
    Window &getWindow();

  private:
    std::unique_ptr<Window> m_window;
    bool m_isRunning = true;
    static Application *s_Instance;

    EventsDispatcher m_eventDispatcher;

    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<VertexArray> m_vertexArray;
  };

  // Defined Client Side
  Application *CreateApplication();
}; // namespace Zen

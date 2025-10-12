#pragma once

#include <zen/core/ZEN_Core.h>
#include <zen/core/ZEN_Window.h>
#include <zen/events/ZEN_Event.h>
#include <zen/events/ZEN_EventBuffer.h>
#include <zen/events/ZEN_Events.h>
#include <zen/gui/ZEN_ImGuiLayer.h>
#include <zen/inputs/ZEN_InputSystem.h>
#include <zen/layer/ZEN_LayerList.h>
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
    bool onEvent(const ZenEvent &event) override;
    void onUpdate(DeltaTime deltaTime);

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *overlay);
    void popLayer(Layer *layer);
    void popOverlay(Layer *overlay);

    static Application &get();
    Window &getWindow();
    int getPriority() const override;

  private:
    static Application *s_instance;
    std::unique_ptr<Window> m_window;
    LayerList m_layerList;
    EventsDispatcher m_eventsDispatcher;
    bool m_isRunning     = true;
    float m_previousTime = 0.0f;

    EventBuffer m_eventBuffer{512};
    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<VertexArray> m_vertexArray;
    InputSystem m_inputSystem;
    ImGuiLayer *m_ImGui = nullptr;
  };

  // Defined Client Side
  Application *CreateApplication();
}; // namespace Zen

#include <include/imgui/imgui_impl_sdl3.h>
#include <vector>
#include <zen/core/ZEN_Application.h>
#include <zen/core/ZEN_Window.h>
#include <zen/gui/ZEN_ImGuiLayer.h>
#include <zen/inputs/ZEN_Input.h>
#include <zen/log/ZEN_Log.h>
#include <zen/particles/ZEN_ParticleTestLayer.h>
#include <zen/time/ZEN_EngineTime.h>

namespace Zen {
  Application *Application::s_instance = nullptr;

  Application::Application() {
    s_instance = this;
    // pushLayer(new ParticleTestLayer());
  };

  Application::~Application() {

  };

  bool Application::init() {
    const bool initSuccess = true;

    Log::init();

    WindowProperties properties = {"Zen Window Test", 1280, 720, true, false};
    m_eventsDispatcher.registerListener(this);
    m_window = Window::create();
    if (!m_window->init(properties)) {
      ZEN_LOG_CRITICAL("[Zen/Core/Application] ZEN_Window failed to initialize properly");
      m_isRunning = false;
      return !initSuccess;
    };

    m_eventsDispatcher.registerListener(m_window.get());

    m_ImGui = new ImGuiLayer;

    pushLayer(m_ImGui);
    ZEN_LOG_DEBUG("[Zen/Core/Application] Pushing a new ImGui layer");

    return initSuccess;
  };

  bool Application::onEvent(const ZenEvent &event) {
    if (event.header.type == EventType::Quit) {
      ZEN_LOG_INFO("Quitting!");
      m_isRunning = false;
      return true;
    };
    return false;
  }

  void Application::run() {
    ZEN_LOG_INFO("Running Application...");
    while (m_isRunning) {
      float currentTime = EngineTime::getTime();

      DeltaTime dt   = currentTime - m_previousTime;
      m_previousTime = currentTime;

      m_inputSystem.begin();

      SDL_Event eventFromSDL;
      while (SDL_PollEvent(&eventFromSDL)) {
        ImGui_ImplSDL3_ProcessEvent(&eventFromSDL);

        ZenEvent e = TranslateEvent(eventFromSDL);
        if (e.header.type != EventType::None) {
          m_eventBuffer.enqueue(e);
        }
      }
      m_ImGui->begin();
      while (!m_eventBuffer.isEmpty()) {
        m_eventsDispatcher.dispatch(m_eventBuffer.dequeue());
      }

      Input::bind(&m_inputSystem);
      for (auto &layer : m_layerList) {
        layer->onUpdate(dt);
      }

      for (auto &layer : m_layerList) {
        layer->onGUIRender();
      }

      Input::unbind();

      m_ImGui->end();
      m_inputSystem.end();
      m_window->onUpdate();
    };

    ZEN_LOG_INFO("Closing Application...");
  };

  void Application::onUpdate(DeltaTime deltaTime) {}

  void Application::pushLayer(Layer *layer) {
    m_layerList.pushLayer(layer);
    m_eventsDispatcher.registerListener(layer);
    layer->onAttach();
  }

  void Application::pushOverlay(Layer *overlay) {
    m_layerList.pushLayer(overlay);
    m_eventsDispatcher.registerListener(overlay);
    overlay->onAttach();
  }

  void Application::popLayer(Layer *layer) {
    layer->onDetach();
    m_layerList.popLayer(layer);
    m_eventsDispatcher.unregisterListener(layer);
  }

  void Application::popOverlay(Layer *overlay) {
    overlay->onDetach();
    m_layerList.popLayer(overlay);
    m_eventsDispatcher.unregisterListener(overlay);
  }

  Application &Application::get() { return *s_instance; }

  Window &Application::getWindow() { return *m_window; };

  int Application::getPriority() const { return 1; }
}; // namespace Zen

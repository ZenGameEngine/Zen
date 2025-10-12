#include "zen/gui/ZEN_ImGuiLayer.h"
#include "zen/log/ZEN_Log.h"
#include <include/imgui/imgui_impl_sdl3.h>
#include <zen/core/ZEN_Application.h>
#include <zen/core/ZEN_Window.h>

namespace Zen {
  Application *Application::s_instance = nullptr;

  Application::Application() {
    WindowProperties properties = {"Zen Window Test", 1280, 720, true, false};
    m_eventDispatcher.registerListener(this);
    m_window = Window::create(properties, &m_eventDispatcher);

    m_vertexArray.reset(VertexArray::Create());

    float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f,
                             0.8f,  0.2f,  1.0f, 0.0f, 0.5f, 0.0f, 0.2f, 0.2f, 0.8f,  1.0f};

    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
    BufferLayout layout = {
        {ShaderDataType::Float3, "a_position"},
        {ShaderDataType::Float4, "a_color"   }
    };
    m_vertexBuffer->setLayout(layout);

    m_vertexArray->addVertexBuffer(m_vertexBuffer);

    uint32_t indices[3] = {0, 1, 2};

    std::shared_ptr<IndexBuffer> m_indexBuffer;
    m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    m_vertexArray->setIndexBuffer(m_indexBuffer);

    const char *base  = SDL_GetBasePath();
    std::string vPath = std::string(base) + "data/basic.vert";
    std::string fPath = std::string(base) + "data/basic.frag";
    m_shader          = std::make_unique<Shader>(vPath.c_str(), fPath.c_str());

    // m_ImGui = new ImGuiLayer();
  };

  Application::~Application() {

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

      m_inputSystem.begin();
      SDL_Event eventFromSDL;
      while (SDL_PollEvent(&eventFromSDL)) {
        // ImGui_ImplSDL3_ProcessEvent(&eventFromSDL);

        ZenEvent e = TranslateEvent(eventFromSDL);
        if (e.header.type != EventType::None) {
          m_eventBuffer.enqueue(e);
        }
      }

      while (!m_eventBuffer.isEmpty()) {
        m_eventDispatcher.dispatch(m_eventBuffer.dequeue());
      }
      // m_ImGui->begin();

      // m_ImGui->end();
      RenderCommand::setClearColour({0.2f, 0.2f, 0.2f, 1.0f});
      RenderCommand::clear();
      m_vertexArray->bind();
      m_shader->bind();
      RenderCommand::drawIndexed(m_vertexArray);

      m_inputSystem.end();
      m_window->onUpdate();
    };
    ZEN_LOG_INFO("Closing Application...");
  };

  int Application::getPriority() const { return 1; }

  Application &Application::get() { return *s_instance; }

  Window &Application::getWindow() { return *m_window; };
}; // namespace Zen

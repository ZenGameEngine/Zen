#include "zen/zen_pch.h"
#include <SDL3/SDL_error.h>
#include <zen/events/ZEN_Event.h>
#include <zen/platform/linux/ZEN_LinuxWindow.h>

namespace {
  void handleError(const char *errorMsg) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Zen Error", errorMsg, nullptr);
    ZEN_LOG_ERROR("[Zen/Platform/LinuxWindow] {}", errorMsg);
  };
} // namespace

namespace Zen {
  static bool s_SDLInitialized = false;

  LinuxWindow::LinuxWindow() {};

  LinuxWindow::~LinuxWindow() { shutdown(); };

  // TEMP MUST CHANGE
  WindowData &LinuxWindow::getWindowData() { return m_windowData; };

  WindowProperties &LinuxWindow::getProperties() { return m_windowProperties; };

  bool LinuxWindow::init(const WindowProperties &properties) {
    const bool initSuccess = true;

    m_windowProperties.title  = properties.title;
    m_windowProperties.width  = properties.width;
    m_windowProperties.height = properties.height;

    ZEN_LOG_DEBUG("Creating new SDL Window: {}, W:{} H: {}",
                  m_windowProperties.title,
                  m_windowProperties.width,
                  m_windowProperties.height);

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
      handleError(SDL_GetError());
      return !initSuccess;
    };

    ZEN_LOG_DEBUG("[Zen/Platform/LinuxWindow] SDL Successfully Initialized!");
    constexpr SDL_WindowFlags flags = SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS |
                                      SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_MOUSE_CAPTURE |
                                      SDL_WINDOW_RESIZABLE;

    // UNCOMMENT BELOW TO FORCE ERROR
    // SDL_WindowFlags flags;
    m_windowData.window = SDL_CreateWindow(m_windowProperties.title.c_str(),
                                           m_windowProperties.width,
                                           m_windowProperties.height,
                                           flags);
    if (m_windowData.window == nullptr) {
      const char *error = SDL_GetError();
      handleError(SDL_GetError());
      return !initSuccess;
    };

    m_windowData.context = GraphicsContext::Create(m_windowData.window);
    m_windowData.context->init();
    if (m_windowData.context == nullptr) {
      handleError(SDL_GetError());
      return !initSuccess;
    };

    int version =
        gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress); // Comment out this line and uncomment next
                                                         // line to force error
    // int version = 0;
    if (version == 0) {
      handleError("[Zen/Platform/LinuxWindow] glad failed to load OpenGL functions");
      return !initSuccess;
    };

    ZEN_LOG_DEBUG("Loaded OpenGL {}.{} w/ glad",
                  GLAD_VERSION_MAJOR(version),
                  GLAD_VERSION_MINOR(version));

    setVSync(m_windowProperties.vsync);
    ZEN_LOG_DEBUG("[Zen/Platform/LinuxWindow] Window successfully initialized!");

    return initSuccess;
  };

  bool LinuxWindow::onEvent(const ZenEvent &event) {
    if (event.header.type == EventType::WindowResize) {
      return resizeEvent(event);
    }

    if (event.header.type == EventType::MouseButtonPressed) {
      return mouseClickEvent(event);
    }

    return false;
  }

  void *LinuxWindow::nativeWindow() const { return m_windowData.window; }

  GraphicsContext &LinuxWindow::context() { return *m_windowData.context; }

  const GraphicsContext &LinuxWindow::context() const { return *m_windowData.context; };
  void LinuxWindow::shutdown() {
    m_windowData.context->shutdown();
    SDL_DestroyWindow(m_windowData.window);
    ZEN_LOG_DEBUG("[Zen/Platform/LinuxWindow] SDL Window destroyed");

    SDL_Quit();
    ZEN_LOG_DEBUG("[Zen/Platform/LinuxWindow] SDL Quit");
  };

  void LinuxWindow::onUpdate() { m_windowData.context->swapBuffers(); };

  uint32_t LinuxWindow::getWidth() { return m_windowProperties.width; };

  uint32_t LinuxWindow::getHeight() { return m_windowProperties.height; };

  void LinuxWindow::setVSync(bool enabled) {
    if (enabled) {
      SDL_GL_SetSwapInterval(1);
      ZEN_LOG_INFO("[Zen/Platform/LinuxWindow] VSync On");

    } else {
      SDL_GL_SetSwapInterval(0);
      ZEN_LOG_INFO("[Zen/Platform/LinuxWindow] VSync Off");
    };
  };

  bool LinuxWindow::getVSync() const { return m_windowProperties.vsync; };

  void LinuxWindow::toggleFullscreen() {
    m_windowProperties.fullscreen = !m_windowProperties.fullscreen;
    SDL_SetWindowFullscreen(m_windowData.window, m_windowProperties.fullscreen);
  };

  // This should ONLY BE CALLED ON THE MAIN THREAD

  bool LinuxWindow::resizeEvent(const ZenEvent &event) {

    int newWidth  = event.windowResize.width;
    int newHeight = event.windowResize.height;

    ZEN_LOG_TRACE("[Zen/Platform/LinuxWindow] Window Width: {}", newWidth);
    ZEN_LOG_TRACE("[Zen/Platform/LinuxWindow] Window Height: {}", newHeight);

    m_windowProperties.width  = newWidth;
    m_windowProperties.height = newHeight;

    ZEN_LOG_TRACE("[Zen/Platform/LinuxWindow] New WinProp Width: {}", m_windowProperties.width);
    ZEN_LOG_TRACE("[Zen/Platform/LinuxWindow] New WinProp Height: {}", m_windowProperties.height);

    return false;
  };

  bool LinuxWindow::mouseClickEvent(const ZenEvent &event) {
    ZEN_LOG_TRACE("[Zen/Platform/LinuxWindow] Mouse click at X: {}, Y: {}",
                  event.mouseButton.x,
                  event.mouseButton.y);
    return false;
  };

  int LinuxWindow::getPriority() const { return 99; }
}; // namespace Zen

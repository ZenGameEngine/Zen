#include <zen/events/ZEN_Event.h>
#include <zen/platform/linux/ZEN_LinuxWindow.h>

namespace Zen {
  static bool s_SDLInitialized = false;

  LinuxWindow::LinuxWindow(const WindowProperties &properties) { init(properties); };

  LinuxWindow::~LinuxWindow() { shutdown(); };

  // TEMP MUST CHANGE
  WindowData &LinuxWindow::getWindowData() { return m_windowData; };

  WindowProperties &LinuxWindow::getProperties() { return m_windowProperties; };

  void LinuxWindow::init(const WindowProperties &properties) {
    m_windowProperties.title  = properties.title;
    m_windowProperties.width  = properties.width;
    m_windowProperties.height = properties.height;

    ZEN_LOG_INFO("Creating new SDL Window: {}, W:{} H: {}",
                 m_windowProperties.title,
                 m_windowProperties.width,
                 m_windowProperties.height);
    if (!s_SDLInitialized) {
      bool success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
      if (!success) {
        const char *error = SDL_GetError();
        emitErrorMessage(error);
        ZEN_LOG_ERROR("SDL was not initialized properly: {}", error);
      };

      ZEN_LOG_INFO("SDL Successfully Initialized!");
      s_SDLInitialized = true;
    };

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
      emitErrorMessage(error);
      ZEN_LOG_ERROR("The SDL Window could not be initialized. {}", error);
    };

    m_windowData.context = GraphicsContext::Create(m_windowData.window);
    m_windowData.context->init();
    if (m_windowData.context == nullptr) {
      const char *error = SDL_GetError();
      emitErrorMessage(error);
      ZEN_LOG_ERROR("The SDL OpenGL context could not be initialized: {}", error);
    };

    gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

    setVSync(m_windowProperties.vsync);

    ZEN_LOG_INFO("Window Successfully Initialized!");
  };

  bool LinuxWindow::onEvent(const ZenEvent &event) {
    // Handles if the event provided is something we care about or not
    if (event.header.type == EventType::WindowResize) {
      return resizeEvent(event);
    }

    // Makes sure the event is what we want
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
    ZEN_LOG_INFO("SDL Window destroyed");
    SDL_Quit();
    ZEN_LOG_INFO("SDL Quit");
  };

  void LinuxWindow::onUpdate() { m_windowData.context->swapBuffers(); };

  uint32_t LinuxWindow::getWidth() { return m_windowProperties.width; };

  uint32_t LinuxWindow::getHeight() { return m_windowProperties.height; };

  void LinuxWindow::setVSync(bool enabled) {
    if (enabled) {
      SDL_GL_SetSwapInterval(1);
      ZEN_LOG_INFO("VSync On");

    } else {
      SDL_GL_SetSwapInterval(0);
      ZEN_LOG_INFO("VSync Off");
    };
  };

  bool LinuxWindow::isVSyncEnabled() const { return m_windowProperties.vsync; };

  void LinuxWindow::toggleFullscreen() {
    m_windowProperties.fullscreen = !m_windowProperties.fullscreen;
    SDL_SetWindowFullscreen(m_windowData.window, m_windowProperties.fullscreen);
  };

  void LinuxWindow::setEventCallback(const EventCallbackFunction &callback) {
    m_eventCallbackFunction = callback;
  };

  // This should ONLY BE CALLED ON THE MAIN THREAD
  void LinuxWindow::emitErrorMessage(const char *message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Zen Error", message, nullptr);
  };

  bool LinuxWindow::resizeEvent(const ZenEvent &event) {

    int newWidth, newHeight;
    SDL_GetWindowSize(m_windowData.window, &newWidth, &newHeight);

    // Logs the new window width and height
    ZEN_LOG_INFO("Window Width: {}", newWidth);
    ZEN_LOG_INFO("Window Height: {}", newHeight);

    // Assigns the window properties to their new values
    m_windowProperties.width  = newWidth;
    m_windowProperties.height = newHeight;

    // Checks to test if the window properties was actually changed by the
    // above assignments to newWidth and newHeight respectively.
    ZEN_LOG_INFO("New WinProp Width: {}", m_windowProperties.width);
    ZEN_LOG_INFO("New WinProp Height: {}", m_windowProperties.height);

    return true;
  };

  bool LinuxWindow::mouseClickEvent(const ZenEvent &event) {
    // Use the event data provided
    ZEN_LOG_INFO("Mouse click at X: {}, Y: {}", event.mouseButton.x, event.mouseButton.y);
    return true;
  };

  int LinuxWindow::getPriority() const { return 99; }
}; // namespace Zen

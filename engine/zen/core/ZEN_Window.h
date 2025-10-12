#pragma once

#include <zen/core/ZEN_Core.h>
#include <zen/renderer/ZEN_GraphicsContext.h>
#include <zen/zen_pch.h>

#ifndef __ZEN_GLAD_H
  #include <glad/gl.h>
#endif // !__ZEN_GLAD_H

namespace Zen {
  struct WindowProperties {
    std::string title;
    uint32_t width;
    uint32_t height;
    bool vsync;
    bool fullscreen;

    WindowProperties(const std::string title = "Zen Application",
                     uint32_t width          = 1280,
                     uint32_t height         = 720,
                     bool vsync              = false,
                     bool fullscreen         = false) {
      this->title      = title;
      this->width      = width;
      this->height     = height;
      this->vsync      = vsync;
      this->fullscreen = fullscreen;
    };
  };

  class Window : public EventListener {
  public:
    using EventCallbackFunction = std::function<void(SDL_Event &)>;

    virtual ~Window() {};

    virtual void onUpdate()      = 0;
    virtual uint32_t getWidth()  = 0;
    virtual uint32_t getHeight() = 0;

    virtual void setVSync(bool enabled) = 0;
    virtual bool isVSyncEnabled() const = 0;
    virtual void toggleFullscreen()     = 0;

    virtual void setEventCallback(const EventCallbackFunction &callback) = 0;

    virtual void emitErrorMessage(const char *message) = 0;

    static std::unique_ptr<Window>
    create(const Zen::WindowProperties &properties = WindowProperties(),
           Zen::EventsDispatcher *dispatcher       = nullptr);

    virtual bool onEvent(const ZenEvent &event) = 0;

    virtual void *nativeWindow() const             = 0; // SDL_Window* as void*
    virtual GraphicsContext &context()             = 0;
    virtual const GraphicsContext &context() const = 0;
  };
}; // namespace Zen

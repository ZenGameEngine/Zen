#pragma once

#include <zen/core/ZEN_Core.h>
#include <zen/core/ZEN_Window.h>
#include <zen/renderer/ZEN_GraphicsContext.h>
#include <zen/zen_pch.h>

namespace Zen {
// TEMP
struct WindowData {
    SDL_Window *window;
    std::unique_ptr<GraphicsContext> context;
};

class LinuxWindow : public Window {
  public:
    LinuxWindow(const WindowProperties &properties,
                EventsDispatcher *dispatcher);
    virtual ~LinuxWindow();

    void onUpdate() override;
    uint32_t getWidth() override;
    uint32_t getHeight() override;

    void setVSync(bool enabled) override;
    bool isVSyncEnabled() const override;
    void toggleFullscreen() override;

    void setEventCallback(const EventCallbackFunction &callback) override;
    void emitErrorMessage(const char *message) override;

    // TEMP
    WindowData &getWindowData();
    WindowProperties &getProperties();

    bool resizeEvent(const SDL_Event &event);
    bool mouseClickEvent(const SDL_Event &event);
    bool onEvent(const SDL_Event &event) override;

  private:
    virtual void init(const WindowProperties &properties,
                      EventsDispatcher *dispatcher);
    virtual void shutdown();

  private:
    EventCallbackFunction m_eventCallbackFunction;

    // TEMP
    WindowData m_windowData;

    WindowProperties m_windowProperties;
};
}; // namespace Zen

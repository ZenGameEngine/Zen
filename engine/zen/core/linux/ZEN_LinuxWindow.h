#pragma once

#include <zen/core/ZEN_Core.h>
#include <zen/core/ZEN_Window.h>
#include <zen/renderer/abstractions/ZEN_GraphicsContext.h>
#include <zen/zen_pch.h>

namespace Zen {
  // TEMP
  struct WindowData {
    SDL_Window *window;
    std::unique_ptr<GraphicsContext> context;
  };

  class LinuxWindow : public Window {
  public:
    LinuxWindow();
    virtual ~LinuxWindow();

    bool init(const WindowProperties &properties) override;

    void onUpdate() override;
    uint32_t getWidth() override;
    uint32_t getHeight() override;

    void setVSync(bool enabled) override;
    bool getVSync() const override;
    void toggleFullscreen() override;

    // TEMP
    WindowData &getWindowData();
    WindowProperties &getProperties();

    bool resizeEvent(const ZenEvent &event);
    bool mouseClickEvent(const ZenEvent &event);

    bool onEvent(const ZenEvent &event) override;
    int getPriority() const override;

    void *nativeWindow() const override;
    GraphicsContext &context() override;
    const GraphicsContext &context() const override;

  private:
    void shutdown();

    // TEMP
    WindowData m_windowData;

    WindowProperties m_windowProperties;
  };
}; // namespace Zen

#include <zen/core/ZEN_Platform.h>
#include <zen/core/ZEN_Window.h>
#include <zen/platform/linux/ZEN_LinuxWindow.h>

namespace Zen {
  std::unique_ptr<Window> Window::create() {
#ifdef __ZEN_PLATFORM_LINUX
    ZEN_LOG_INFO("[Zen/Core/Window] Creating a Linux Window...");
    return std::make_unique<LinuxWindow>();
#endif // __ZEN_PLATFORM_LINUX
#ifdef __ZEN_PLATFORM_WINDOWS
    ZEN_LOG_INFO("[Zen/Core/Window] Creating a Windows window...");
    return std::make_unique<WIN32Window>();
#endif // __ZEN_PLATFORM_WINDOWS
    ZEN_LOG_ERROR("[Zen/Core/Window] The current OS is unsupported");
    return nullptr;
  };

}; // namespace Zen

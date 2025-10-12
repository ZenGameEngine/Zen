#include <zen/core/ZEN_Window.h>
#include <zen/platform/linux/ZEN_LinuxWindow.h>

namespace Zen {
  std::unique_ptr<Window> Window::create(const Zen::WindowProperties &properties) {
#ifdef __ZEN_PLATFORM_LINUX
    ZEN_LOG_INFO("Creating a Linux Window...");
    return std::make_unique<LinuxWindow>(properties);
#endif              // __ZEN_PLATFORM_LINUX
#ifdef __ZEN_PLATFORM_WINDOWS
    return nullptr; // NOT SUPPORTED
#endif              // __ZEN_PLATFORM_WINDOWS
    // Unsupported OS
    return nullptr;
  };

}; // namespace Zen

#pragma once


#include <zen/platform/linux/ZEN_LinuxWindow.h>

#if defined(__ZEN_PLATFORM_WINDOWS) || defined(__ZEN_PLATFORM_LINUX)
namespace Zen {
    using WIN32Window = LinuxWindow;
}
#endif

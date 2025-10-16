#pragma once

#include <zen/core/ZEN_Application.h>
#include <zen/core/ZEN_Core.h>
#include <zen/core/ZEN_Platform.h>

#ifdef __ZEN_PLATFORM_LINUX
extern Zen::Application *Zen::CreateApplication();

int main(int argc, char *argv[]) {
  Zen::Log::init();
  ZEN_LOG_INFO("Hello, Linux!");

  auto app = Zen::CreateApplication();
  app->run();

  ZEN_LOG_INFO("Deleting app...");
  delete app;
};

#endif // __ZEN_PLATFORM_LINUX

#ifdef __ZEN_PLATFORM_WINDOWS
extern Zen::Application *Zen::CreateApplication();
  #include <windows.h>
  #if defined(_WIN32) && defined(_MSC_VER)
int main(int argc, char* argv[]);
int WINAPI WinMain(HINSTANCE /*hInstance*/,
                   HINSTANCE /*hPrevInstance*/,
                   LPSTR /*lpCmdLine*/,
                   int /*nCmdShow*/) {
  /*  __argc and __argv are MSVC’s built‑in variables that contain the
   *  command‑line arguments.  Forward them to the real main().            */
  return main(__argc, __argv);
}
  #endif

int main(int argc, char *argv[]) {
  Zen::Log::init();
  ZEN_LOG_INFO("Hello, Windows!");

  Zen::Application *app = Zen::CreateApplication();
  app->run();

  ZEN_LOG_INFO("Deleting app...");
  delete app;
  return 0;
}

#endif __ZEN_PLATFORM_WINDOWS

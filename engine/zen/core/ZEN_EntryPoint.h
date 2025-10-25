#pragma once

#include <zen/core/ZEN_Application.h>
#include <zen/core/ZEN_Core.h>
#include <zen/core/ZEN_Platform.h>

#include <zen/utility/ZEN_Macros.h>

#ifdef __ZEN_PLATFORM_LINUX
extern Zen::Application *Zen::CreateApplication();

int main(int argc, char *argv[]) {
  ZEN_LOG_INFO("[Zen/Core/EntryPoint] Hello, Linux!   :)");

  ZEN_START_PROFILE_SESSION("Zen Init", "gInitProfile.json");
  auto app = Zen::CreateApplication();
  if (!app->init()) {
    ZEN_LOG_CRITICAL("[Zen/Core/EntryPoint] Application failed to initialize :(");
    delete app;
    return EXIT_FAILURE;
  };
  ZEN_END_PROFILE_SESSION();

  ZEN_START_PROFILE_SESSION("Zen Register Layers", "gRegisterLayerProfile.json");
  app->registerLayers();
  ZEN_END_PROFILE_SESSION();

  ZEN_START_PROFILE_SESSION("Zen Run App", "gRunProfile.json");
  app->run();
  ZEN_END_PROFILE_SESSION();

  ZEN_START_PROFILE_SESSION("Zen Delete", "gDeleteProfile.json");
  ZEN_LOG_INFO("[Zen/Core/EntryPoint] Deleting app...");
  delete app;
  ZEN_END_PROFILE_SESSION();

  return EXIT_SUCCESS;
};

#endif // __ZEN_PLATFORM_LINUX

#ifdef __ZEN_PLATFORM_WINDOWS
extern Zen::Application *Zen::CreateApplication();
  #include <windows.h>
  #if defined(_WIN32) && defined(_MSC_VER)
int main(int argc, char *argv[]);
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
  ZEN_LOG_INFO("Hello, Windows!   :)");

  auto app = Zen::CreateApplication();
  if (!app->init()) {
    ZEN_LOG_CRITICAL("[Zen/Core/EntryPoint] Application failed to initialize :(");
    delete app;
    return EXIT_FAILURE;
  };

  app->registerLayers();

  app->run();

  ZEN_LOG_INFO("[Zen/Core/EntryPoint] Deleting app...");
  delete app;

  return EXIT_SUCCESS;
}

#endif //__ZEN_PLATFORM_WINDOWS

#pragma once

#include <zen/core/ZEN_Application.h>
#include <zen/core/ZEN_Core.h>

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
// NOT USED YET
#endif // __ZEN_PLATFORM_LINUX

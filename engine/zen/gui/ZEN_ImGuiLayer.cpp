#include "zen/events/ZEN_Event.h"
#include <SDL3/SDL_video.h>
#include <include/imgui/imgui.h>
#include <include/imgui/imgui_impl_opengl3.h>
#include <include/imgui/imgui_impl_sdl3.h>
#include <zen/core/ZEN_Application.h>
#include <zen/gui/ZEN_ImGuiLayer.h>
#include <zen/gui/ZEN_Style.h>
#include <zen/time/ZEN_DeltaTime.h>
#include <zen/utility/ZEN_Macros.h>

namespace Zen {
  void ImGuiLayer::onAttach() {
    ZEN_LOG_TRACE("ATTACHING");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ZEN_LOG_TRACE("imgui context created");
    ImGuiIO &io = ImGui::GetIO();

    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;

    styleSetup();
    ZEN_LOG_TRACE("style setup?");
    const char *glslVersion = "#version 430";
    Application &app        = Application::get();
    ZEN_LOG_TRACE("app gotten");
    SDL_Window *window = static_cast<SDL_Window *>(app.getWindow().nativeWindow());
    ZEN_LOG_TRACE("window gotten");
    SDL_GLContext context = static_cast<SDL_GLContext>(app.getWindow().context().nativeContext());

    ZEN_LOG_TRACE("Imgui init");
    ImGui_ImplSDL3_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init(glslVersion);
  }

  void ImGuiLayer::onDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
  }

  void ImGuiLayer::onUpdate(DeltaTime deltaTime) {
    // ImGui::ShowDemoWindow();
  }

  bool ImGuiLayer::onEvent(const ZenEvent &event) {
    ImGuiIO &io = ImGui::GetIO(); // valid after NewFrame()
    switch (event.header.type) {
      case EventType::MouseMoved:
      case EventType::MouseButtonPressed:
      case EventType::MouseButtonReleased:
      case EventType::MouseScrolled:
        return io.WantCaptureMouse;
      case EventType::KeyPressed:
      case EventType::KeyReleased:
        return io.WantCaptureKeyboard;
      case EventType::TextInput:
        return io.WantTextInput;
      default:
        return false;
    }
  }

  void ImGuiLayer::begin() {
    // LOG_INFO("new frame");
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    // LOG_INFO("Done begin frame");
  }

  void ImGuiLayer::end() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO &io = ImGui::GetIO();

    Application &app = Application::get();
    io.DisplaySize = ImVec2((float)app.getWindow().getWidth(), (float)app.getWindow().getHeight());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      SDL_Window *backup_current_window    = SDL_GL_GetCurrentWindow();
      SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }
  }
} // namespace Zen

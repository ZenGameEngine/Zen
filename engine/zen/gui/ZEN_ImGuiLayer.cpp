#include <SDL3/SDL_video.h>
#include <zen/core/ZEN_Application.h>
#include <zen/gui/ZEN_ImGuiLayer.h>
#include <zen/gui/ZEN_Style.h>
#include <include/imgui/imgui.h>
#include <include/imgui/imgui_impl_opengl3.h>
#include <include/imgui/imgui_impl_sdl3.h>

namespace Zen {
  void ImGuiLayer::onAttach() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;

    styleSetup();

    const char *glslVersion = "#version 430";
    Application &app        = Application::get();
    SDL_Window *window      = static_cast<SDL_Window *>(app.getWindow().nativeWindow());
    SDL_GLContext context   = static_cast<SDL_GLContext>(app.getWindow().context().nativeContext());

    ImGui_ImplSDL3_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init(glslVersion);
  }

  void ImGuiLayer::onDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
  }

  void ImGuiLayer::onUpdate() {
    // LOG_INFO("on update imgui");
    ImGui::ShowDemoWindow(); // This will show the ImGui demo window
    // OG_INFO("show");
  }

  bool ImGuiLayer::onEvent(const SDL_Event &event) { return false; }

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
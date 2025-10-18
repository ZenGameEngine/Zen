#include "DemoSwitcher.h"
#include <zen/core/ZEN_Application.h>
#include <zen/inputs/ZEN_KeyCodes.h>
#include <zen/log/ZEN_Log.h>


namespace Zen {

  void DemoSwitcher::onAttach() {
    m_gameLayer = new GameLayer();
    Application::get().pushLayer(m_gameLayer);
    m_currentActive = m_gameLayer;
    m_particleLayer = nullptr;
    m_isShowingGame = true; // start with game
  }

  void DemoSwitcher::onUpdate(DeltaTime deltaTime) {
    m_seconds += deltaTime;
    if (Input::isKeyHeld(Key::F1)) {
      if (m_seconds >= 1) { // its to make sure that the layers are updated first
                            // need to implement safe guard for mutating layer list
        switchDemo();
        m_seconds = 0;
      }
    }
  }

  void DemoSwitcher::switchDemo() {

    Application::get().popLayer(m_currentActive);

    m_isShowingGame = !m_isShowingGame;

    if (m_isShowingGame) {
      m_gameLayer = new GameLayer();
      Application::get().pushLayer(m_gameLayer);
      m_currentActive = m_gameLayer;
      ZEN_LOG_INFO("Switched to Game Demo");
    } else {
      m_particleLayer = new ParticleTestLayer();
      Application::get().pushLayer(m_particleLayer);
      m_currentActive = m_particleLayer;
      ZEN_LOG_INFO("Switched to Particle Demo");
    }
  }

  void DemoSwitcher::onGUIRender() {
    ImGuiViewport *vp = ImGui::GetMainViewport();
    const float PAD   = 10.0f;

    const ImGuiWindowFlags hud = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings |
                                 ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize;

    ImGui::SetNextWindowViewport(vp->ID);
    ImGui::SetNextWindowPos(ImVec2(vp->WorkPos.x + PAD, vp->WorkPos.y + vp->WorkSize.y - PAD),
                            ImGuiCond_Always,
                            ImVec2(0.0f, 1.0f));
    ImGui::SetNextWindowBgAlpha(0.6f);
    ImGui::SetNextWindowSize(ImVec2(240.0f, 0.0f), ImGuiCond_Always);
    ImGui::Begin("Demo Switcher", nullptr, hud);
    if(m_isShowingGame) {
      ImGui::Text("Currently in: Game demo");
    } else {
      ImGui::Text("Currently in: Particle demo");
    }
    if (ImGui::Button("Switch Demo (F1)",ImVec2(-1, 0))) {
      switchDemo();
    }
    ImGui::End();
  }
} // namespace Zen


#include "zen/time/ZEN_DeltaTime.h"
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <include/imgui/imgui.h>
#include <zen/gui/ZEN_Style.h>
#include <zen/inputs/ZEN_KeyCodes.h>
#include <zen/particles/ZEN_ParticleSystem.h>
#include <zen/particles/ZEN_ParticleTestLayer.h>
#include <zen/renderer/ZEN_RenderCommand.h>
#include <zen/renderer/ZEN_Renderer.h>

namespace Zen {
  void ParticleTestLayer::onAttach() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_camera.setPosition({0.0f, 0.0f, 0.0f});
    m_camera.setOrthographic(m_worldMin.x, m_worldMax.x, m_worldMin.y, m_worldMax.y);
    m_cameraController.enableWorldBounds(true);

    m_shader         = std::make_shared<Shader>("data/particle.vert", "data/particle.frag");
    m_particleSystem = std::make_unique<ParticleSystem>(m_capacity);
    m_quadBuilder.init(m_shader);

    m_particleEmitter.pos               = {0, 0};
    m_particleEmitter.size              = {1, 1};
    m_particleEmitter.colour            = {1.0f, 0.5f, 0, 1.0f};
    m_particleEmitter.spawnRate         = 60;
    m_particleEmitter.props.colourBegin = {1.0f, 0.5f, 0, 1.0f};
    m_particleEmitter.props.colourEnd   = {1.0f, 0, 0, 1.0f};
    m_particleEmitter.props.sizeBegin   = {1, 1};
    m_particleEmitter.props.sizeEnd     = {0, 0};
    m_particleEmitter.props.lifeTime    = 1.0f;
    m_particleEmitter.props.velocity    = {0, 0};
    m_particleEmitter.vRand.coneDeg     = 45.0f;
    m_particleEmitter.vRand.noiseSigma  = 1.0f;
    m_particleEmitter.vRand.speedMaxMul = 1.0f;
    m_particleEmitter.vRand.speedMinMul = 0;

    if (m_stats.gpu_name.empty()) {
      m_stats.gpu_name = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    }
  }

  void ParticleTestLayer::onUpdate(DeltaTime deltaTime) {
    if (m_stats.active) {
      DrawStats::reset();
    }

    m_cameraController.onUpdate(deltaTime);
    RenderCommand::setClearColour({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::clear();

    Renderer::beginScene(m_camera);
    m_particleSystem->updateEmitter(m_particleEmitter, deltaTime);

    m_particleSystem->update(deltaTime);
    m_particleSystem->upload();

    float step = m_speed * (float)deltaTime;
    if (Input::isKeyHeld(Key::Up)) {
      m_particleEmitter.pos.y += step;
    }
    if (Input::isKeyHeld(Key::Down)) {
      m_particleEmitter.pos.y -= step;
    }
    if (Input::isKeyHeld(Key::Right)) {
      m_particleEmitter.pos.x += step;
    }
    if (Input::isKeyHeld(Key::Left)) {
      m_particleEmitter.pos.x -= step;
    }

    const glm::vec2 half  = 0.5f * m_particleEmitter.size;
    const glm::vec2 minP  = m_worldMin + half;
    const glm::vec2 maxP  = m_worldMax - half;
    m_particleEmitter.pos = glm::clamp(m_particleEmitter.pos, minP, maxP);

    m_quadBuilder.drawQuad(m_particleEmitter.pos, m_particleEmitter.size, m_particleEmitter.colour);
    Renderer::submit(m_particleSystem->shader(), m_particleSystem->vao());
    Renderer::endScene();

    if (m_stats.active) {
      startProfiling(deltaTime);
    }
  }

  bool ParticleTestLayer::onEvent(const ZenEvent &event) {
    m_cameraController.onEvent(event);
    if (event.header.type == EventType::WindowResize) {
      RenderCommand::setViewport(event.windowResize.width, event.windowResize.height);
      ZEN_LOG_TRACE("resize viewport");
    }
    return false;
  }

  void ParticleTestLayer::onGUIRender() {
    ImGuiIO &io       = ImGui::GetIO();
    ImGuiViewport *vp = ImGui::GetMainViewport();
    const float PAD   = 10.0f;
    const float GAP   = 8.0f;

    const ImGuiWindowFlags hud = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings |
                                 ImGuiWindowFlags_NoDocking;

    if (m_startup) {
      ImGui::OpenPopup("Welcome to the Demo");
      m_startup = false;
    }

    const ImVec2 center =
        ImVec2(vp->WorkPos.x + vp->WorkSize.x * 0.5f, vp->WorkPos.y + vp->WorkSize.y * 0.5f);
    ImGui::SetNextWindowViewport(vp->ID);
    ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal("Welcome to the Demo", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
      ImGui::SetWindowFontScale(2.0f);
      ImGui::Text("Camera controls - WASD, mouse scroll");
      ImGui::Text("Object controls - Arrow keys");
      if (ImGui::Button("Yes", ImVec2(-1, 0)))
        ImGui::CloseCurrentPopup();
      ImGui::EndPopup();
    }

    ImGui::SetNextWindowViewport(vp->ID);
    ImGui::SetNextWindowPos(ImVec2(vp->WorkPos.x + vp->WorkSize.x - PAD, vp->WorkPos.y + PAD),
                            ImGuiCond_Always,
                            ImVec2(1.0f, 0.0f));
    ImGui::SetNextWindowBgAlpha(0.6f);
    ImGui::SetNextWindowSize(ImVec2(360.0f, 0.0f), ImGuiCond_Always);
    ImGui::Begin("Controls", nullptr, hud);
    ImGui::Text("Camera controls - WASD");
    ImGui::Text("Object controls - Arrow keys");
    const ImVec2 controls_pos  = ImGui::GetWindowPos();
    const ImVec2 controls_size = ImGui::GetWindowSize();
    ImGui::End();

    if (!m_stats.active) {
      ImGui::SetNextWindowViewport(vp->ID);
      ImGui::SetNextWindowPos(ImVec2(vp->WorkPos.x + PAD, vp->WorkPos.y + PAD), ImGuiCond_Always);
      ImGui::Begin("Particle Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
      showHelpMarker("Controls the amount of particles are emitted per second");
      ImGui::SameLine();
      ImGui::DragInt("Spawn Rate (p/s)", &m_spawnRateDummy, 1, 0, m_capacity);
      if (m_spawnRateDummy < 0) {
        m_particleEmitter.spawnRate = 0;
        m_spawnRateDummy            = 0;
      } else if (m_spawnRateDummy > m_capacity) {
        m_particleEmitter.spawnRate = m_capacity;
        m_spawnRateDummy            = m_capacity;
      } else {
        m_particleEmitter.spawnRate = m_spawnRateDummy;
      }

      showHelpMarker("Controls how many seconds until a particle dies after being emitted");
      ImGui::SameLine();
      ImGui::DragFloat("Lifetime (s)", &m_particleEmitter.props.lifeTime, 0.1f, 0.1f, 10.0f);
      showHelpMarker("Controls the velocity of the particles");
      ImGui::SameLine();
      ImGui::DragFloat2("Velocity", &m_particleEmitter.props.velocity[0], 0.1f, -10.0f, 10.0f);
      showHelpMarker("Controls the particles starting colour");
      ImGui::SameLine();
      ImGui::ColorEdit4("Colour Start", &m_particleEmitter.props.colourBegin[0]);
      showHelpMarker("Controls the particles final colour before disappearing");
      ImGui::SameLine();
      ImGui::ColorEdit4("Colour End", &m_particleEmitter.props.colourEnd[0]);
      showHelpMarker("Controls the particles starting width and height");
      ImGui::SameLine();
      ImGui::DragFloat2("Particle Size Start",
                        &m_particleEmitter.props.sizeBegin[0],
                        0.1f,
                        0,
                        10.0f);
      ImGui::SameLine();
      ImGui::Checkbox("##Link Start size", &m_linkStartSize);
      if (m_linkStartSize) {
        m_particleEmitter.props.sizeBegin.y = m_particleEmitter.props.sizeBegin.x;
      }
      showHelpNoMarker("Links width and height \nChange through width");
      showHelpMarker("Controls the particles final width and height before disappearing");
      ImGui::SameLine();
      ImGui::DragFloat2("Particle Size End  ", &m_particleEmitter.props.sizeEnd[0], 0.1f, 0, 10.0f);
      ImGui::SameLine();
      ImGui::Checkbox("##Link End size", &m_linkEndSize);
      if (m_linkEndSize) {
        m_particleEmitter.props.sizeEnd.y = m_particleEmitter.props.sizeEnd.x;
      }
      showHelpNoMarker("Links width and height \nChange through width");
      showHelpMarker("Controls the angle of the particle emission");
      ImGui::SameLine();
      ImGui::DragFloat("Cone (deg)", &m_particleEmitter.vRand.coneDeg, 0.1f, 0, 360.0f);
      showHelpMarker("Controls the minimum emission speed for the velocity randomizer");
      ImGui::SameLine();
      ImGui::DragFloat("Speed min x", &m_particleEmitter.vRand.speedMinMul, 0.01f, 0, 2.0f);
      showHelpMarker("Controls the maximum emission speed for the velocity randomizer");
      ImGui::SameLine();
      ImGui::DragFloat("Speed max x", &m_particleEmitter.vRand.speedMaxMul, 0.01f, 0, 3.0f);
      showHelpMarker("Controls the noise applied on the velocity randomizer");
      ImGui::SameLine();
      ImGui::DragFloat("Noise sigma", &m_particleEmitter.vRand.noiseSigma, 0.01f, 0, 1.0f);

      if (ImGui::Button("Clear All Particles")) {
        m_particleSystem->clear();
      }
      if (ImGui::TreeNode("Emitter Settings")) {
        ImGui::ColorEdit4("Colour", &m_particleEmitter.colour[0]);
        ImGui::DragFloat2("Size", &m_particleEmitter.size[0], 0.1f, 0, 10.0f);
        ImGui::SameLine();
        ImGui::Checkbox("##Link Size", &m_linkEmitterSize);
        if (m_linkEmitterSize) {
          m_particleEmitter.size.y = m_particleEmitter.size.x;
        }
        showHelpNoMarker("Links width and height \nChange through width");
        ImGui::DragFloat("Speed", &m_speed, 0.1f, 0.1f, 10.0f);

        ImGui::Checkbox("Link Start Size", &m_linkEmitterToParticle);
        if (m_linkEmitterToParticle) {
          m_particleEmitter.props.sizeBegin = m_particleEmitter.size;
        }
        showHelpNoMarker("Links width and height of emitter andParticle begin size");

        ImGui::TreePop();
      }
      ImGui::End();
    }
    ImGui::SetNextWindowViewport(vp->ID);
    ImGui::SetNextWindowPos(
        ImVec2(vp->WorkPos.x + vp->WorkSize.x - PAD, controls_pos.y + controls_size.y + GAP),
        ImGuiCond_Always,
        ImVec2(1.0f, 0.0f));
    ImGui::SetNextWindowBgAlpha(0.6f);
    ImGui::SetNextWindowSize(ImVec2(360.0f, 0.0f), ImGuiCond_Always);
    ImGui::Begin("Debug", nullptr, hud);
    ImGui::SeparatorText("Debug Metrics");
    ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::Text("Alive: %d / %i", m_particleSystem->aliveCount(), m_capacity);

    const float pct = (float)m_particleSystem->aliveCount() / (float)m_capacity;
    ImGui::ProgressBar(pct, ImVec2(-1, 0), nullptr);

    const float estAlive = m_particleEmitter.spawnRate * m_particleEmitter.props.lifeTime;
    ImGui::Text("Expected Particles (alive): %.1f", estAlive);
    ImGui::Text("Max Particles (alive): %i", m_capacity);

    ImGui::SeparatorText("Profiling");
    ImGui::SliderFloat("Duration (s)", &m_stats.window_sec, 1.0f, 300.0f, "%.0f");

    if (!m_stats.active) {
      if (ImGui::Button("Start Profiling")) {
        const float keep_window    = m_stats.window_sec;
        const std::string keep_gpu = m_stats.gpu_name.empty()
                                         ? reinterpret_cast<const char *>(glGetString(GL_RENDERER))
                                         : m_stats.gpu_name;

        m_stats            = RunStats{};
        m_stats.window_sec = keep_window;
        m_stats.gpu_name   = keep_gpu;
        m_stats.active     = true;

        ZEN_LOG_INFO("Starting profiling for {} s...", (int)m_stats.window_sec);
      }
      showHelpNoMarker("Press to profile game engine performance");
    } else {
      ImGui::Text("Profiling... %.1f / %.0f s", (float)m_stats.elapsed_sec, m_stats.window_sec);
      ImGui::SameLine();
      if (ImGui::Button("Cancel")) {
        m_stats.active = false;
        ZEN_LOG_INFO("Profiling cancelled.");
      }
      const float profPct = (float)m_stats.elapsed_sec / m_stats.window_sec;
      ImGui::ProgressBar(profPct, ImVec2(-1, 0), nullptr);
    }
    if (m_particleSystem->aliveCount() == m_capacity) {
      ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0, 0, 1.0f));
    } else {
      ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0, 0, 0.0f));
    }
    ImGui::Text("== Saturated ==");
    ImGui::PopStyleColor();
    ImGui::End();
  }

  void ParticleTestLayer::startProfiling(DeltaTime deltaTime) {
    const float dt       = deltaTime.seconds();
    const float frame_ms = deltaTime.milliseconds();
    m_stats.frames++;
    m_stats.elapsed_sec += dt;
    m_stats.sum_ms += frame_ms;
    m_stats.min_ms = std::min(m_stats.min_ms, frame_ms);
    m_stats.max_ms = std::max(m_stats.max_ms, frame_ms);

    m_stats.last_draw_calls = (uint32_t)DrawStats::drawCalls;
    m_stats.total_draw_calls += (uint32_t)DrawStats::drawCalls;

    const int alive_now = m_particleSystem->aliveCount();
    m_stats.sum_alive += (alive_now >= 0 ? (uint64_t)alive_now : 0);
    m_stats.peak_alive = std::max(m_stats.peak_alive, alive_now);

    if (m_stats.elapsed_sec >= (double)m_stats.window_sec && m_stats.frames > 0) {
      const double avg_ms = m_stats.sum_ms / (double)m_stats.frames;
      const double avg_fps =
          (m_stats.elapsed_sec > 0.0) ? ((double)m_stats.frames / m_stats.elapsed_sec) : 0.0;
      const double min_ms = (m_stats.min_ms == FLT_MAX) ? 0.0 : (double)m_stats.min_ms;
      const double max_ms = (double)m_stats.max_ms;

      const double avg_alive         = (double)m_stats.sum_alive / (double)m_stats.frames;
      const double lifetime_s        = (double)m_particleEmitter.props.lifeTime;
      const double achieved_spawn_ps = (lifetime_s > 0.0) ? (avg_alive / lifetime_s) : 0.0;

      const double dps = (m_stats.elapsed_sec > 0.0)
                             ? ((double)m_stats.total_draw_calls / m_stats.elapsed_sec)
                             : 0.0;
      const double dpf =
          (m_stats.frames > 0) ? ((double)m_stats.total_draw_calls / (double)m_stats.frames) : 0.0;

      ZEN_LOG_INFO(" Duration (s): {}\n"
                   " Average FPS: {:.1f}\n"
                   " Frames (total): {}\n"
                   " Frame time (avg): {:.2f} ms\n"
                   " Frame time (min): {:.2f} ms\n"
                   " Frame time (max): {:.2f} ms\n"
                   " Alive particles (avg): {:.1f}\n"
                   "Alive particles (peak): {}\n"
                   " Achieved spawn (p/s): {:.1f}\n"
                   " Lifetime (s): {:.1f}\n"
                   " Target Spawn Rate (p/s): {}\n"
                   " Draw Calls per second: {:.2f}\n"
                   " Draw Calls per frame: {:.2f}\n"
                   " Draw Calls last frame: {}\n"
                   " Draw Calls total: {}\n"
                   " GPU: {}",
                   (int)m_stats.window_sec,
                   avg_fps,
                   m_stats.frames,
                   avg_ms,
                   min_ms,
                   max_ms,
                   avg_alive,
                   m_stats.peak_alive,
                   achieved_spawn_ps,
                   m_particleEmitter.props.lifeTime,
                   (int)m_particleEmitter.spawnRate,
                   dps,
                   dpf,
                   m_stats.last_draw_calls,
                   (uint64_t)m_stats.total_draw_calls,
                   m_stats.gpu_name.c_str());

      m_stats.active = false;
    }
  }

} // namespace Zen

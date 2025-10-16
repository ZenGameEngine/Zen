
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
    m_particleEmitter.spawnRate         = 60.f;
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
  }

  void ParticleTestLayer::onUpdate(DeltaTime deltaTime) {
    m_cameraController.onUpdate(deltaTime);
    RenderCommand::setClearColour({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::clear();

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

    Renderer::beginScene(m_camera);
    m_quadBuilder.drawQuad(m_particleEmitter.pos, m_particleEmitter.size, m_particleEmitter.colour);
    Renderer::submit(m_particleSystem->shader(), m_particleSystem->vao());
    Renderer::endScene();
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
    if (m_startup) {
      ImGui::OpenPopup("Welcome to the Demo");
      m_startup = false;
    }
    if (ImGui::BeginPopupModal("Welcome to the Demo", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
      ImGui::SetWindowFontScale(2.0f);
      ImGui::Text("Camera controls - WASD");
      ImGui::Text("Object controls - Arrow keys");
      if (ImGui::Button("Yes", {-1, 0})) {
        ImGui::CloseCurrentPopup();
      }
      ImGui::EndPopup();
    }

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.6f);
    ImGui::Begin("Score",
                 nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::Text("Camera controls - WASD");
    ImGui::Text("Object controls - Arrow keys");
    ImGui::End();

    ImGuiIO &io = ImGui::GetIO();
    ImGui::SetNextWindowPos({10, 100}, ImGuiCond_Once);
    ImGui::Begin("Particle Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    showHelpMarker("Controls the amount of particles are emitted per second");
    ImGui::SameLine();
    ImGui::DragFloat("Spawn Rate (p/s)", &m_particleEmitter.spawnRate, 1.0f, 0, m_capacity);
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
    ImGui::DragFloat2("Particle Size Start", &m_particleEmitter.props.sizeBegin[0], 0.1f, 0, 10.0f);
    ImGui::SameLine();
    ImGui::Checkbox("##Link Start size", &m_linkStartSize);
    if (m_linkStartSize) {
      m_particleEmitter.props.sizeBegin.y = m_particleEmitter.props.sizeBegin.x;
    }
    if (ImGui::IsItemHovered()) {
      ImGui::BeginTooltip();
      ImGui::PushTextWrapPos(450.0f);
      ImGui::TextUnformatted("Links width and height");
      ImGui::TextUnformatted("Change through width");
      ImGui::PopTextWrapPos();
      ImGui::EndTooltip();
    }
    showHelpMarker("Controls the particles final width and height before disappearing");
    ImGui::SameLine();
    ImGui::DragFloat2("Particle Size End  ", &m_particleEmitter.props.sizeEnd[0], 0.1f, 0, 10.0f);
    ImGui::SameLine();
    ImGui::Checkbox("##Link End size", &m_linkEndSize);
    if (m_linkEndSize) {
      m_particleEmitter.props.sizeEnd.y = m_particleEmitter.props.sizeEnd.x;
    }
    if (ImGui::IsItemHovered()) {
      ImGui::BeginTooltip();
      ImGui::PushTextWrapPos(450.0f);
      ImGui::TextUnformatted("Links width and height");
      ImGui::TextUnformatted("Change through width");
      ImGui::PopTextWrapPos();
      ImGui::EndTooltip();
    }
    showHelpMarker("Controls the angle of the particle emission");
    ImGui::SameLine();
    ImGui::DragFloat("Cone (deg)", &m_particleEmitter.vRand.coneDeg, 0.1f, 0, 60.0f);
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
      ImGui::DragFloat("Width", &m_particleEmitter.size.x, 0.1f, 0, 10.0f);
      ImGui::DragFloat("Height", &m_particleEmitter.size.y, 0.1f, 0, 10.0f);
      ImGui::SameLine();
      if (m_linkEmitterSize) {
        m_particleEmitter.size.y = m_particleEmitter.size.x;
      }
      ImGui::DragFloat("Speed", &m_speed, 0.1f, 0.1f, 10.0f);
      ImGui::Checkbox("Link Size", &m_linkEmitterSize);
      ImGui::Checkbox("Link Start Size", &m_linkEmitterToParticle);
      if (m_linkEmitterToParticle) {
        m_particleEmitter.props.sizeBegin = m_particleEmitter.size;
      }

      ImGui::TreePop();
    }
    ImGui::SeparatorText("Debug Metrics");
    ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::Text("Alive: %d / %i", m_particleSystem->aliveCount(), m_capacity);

    const float pct = (float)m_particleSystem->aliveCount() / (float)m_capacity;
    ImGui::ProgressBar(pct, ImVec2(300.0f, 0), nullptr);

    const float estAlive = m_particleEmitter.spawnRate * m_particleEmitter.props.lifeTime;
    ImGui::Text("Expected Particles (alive): %.1f", estAlive);
    ImGui::Text("Max Particles (alive): %i", m_capacity);
    if (m_particleSystem->aliveCount() == m_capacity) {
      ImGui::TextColored(ImVec4(1.0f, 0, 0, 1.0f), "== Saturated ==");
    }

    ImGui::End();
  }
} // namespace Zen
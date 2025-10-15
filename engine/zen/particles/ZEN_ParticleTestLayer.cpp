
#include "zen/inputs/ZEN_KeyCodes.h"
#include "zen/particles/ZEN_ParticleSystem.h"
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <include/imgui/imgui.h>
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
    m_particleEmitter.props.velocity    = {1, 1};
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

    const glm::vec2 half  = 0.5f * m_particleEmitter.size; // spawn area half-extent
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
    ImGuiIO &io = ImGui::GetIO();

    ImGui::Begin("Particle Settings");
    ImGui::DragFloat("Spawn Rate", &m_particleEmitter.spawnRate, 1.0f, 0, m_capacity);
    ImGui::DragFloat("Lifetime", &m_particleEmitter.props.lifeTime, 0.1f, 0.1f, 3.0f);
    ImGui::DragFloat2("Velocity", &m_particleEmitter.props.velocity[0], 0.1f, -10.0f, 10.0f);
    ImGui::ColorEdit4("Colour Start", &m_particleEmitter.props.colourBegin[0]);
    ImGui::ColorEdit4("Colour End", &m_particleEmitter.props.colourEnd[0]);
    ImGui::DragFloat("Particle Width Start", &m_particleEmitter.props.sizeBegin.x, 0.1f, 0, 10.0f);
    ImGui::DragFloat("Particle Height Start", &m_particleEmitter.props.sizeBegin.y, 0.1f, 0, 10.0f);
    ImGui::DragFloat("Particle Width End", &m_particleEmitter.props.sizeEnd.x, 0.1f, 0, 10.0f);
    ImGui::DragFloat("Particle Height End", &m_particleEmitter.props.sizeEnd.y, 0.1f, 0, 10.0f);
    ImGui::DragFloat("Cone (deg)", &m_particleEmitter.vRand.coneDeg, 0.1f, 0, 60.0f);
    ImGui::DragFloat("Speed min x", &m_particleEmitter.vRand.speedMinMul, 0.01f, 0, 2.0f);
    ImGui::DragFloat("Speed max x", &m_particleEmitter.vRand.speedMaxMul, 0.01f, 0, 3.0f);
    ImGui::DragFloat("Noise sigma", &m_particleEmitter.vRand.noiseSigma, 0.01f, 0, 1.0f);
    ImGui::Text("Particles: %zu", m_particleSystem->capacity());
    if (ImGui::Button("Clear All Particles")) {
      m_particleSystem->clear();
    }
    if (ImGui::TreeNode("Emitter Settings")) {
      ImGui::ColorEdit4("Colour", &m_particleEmitter.colour[0]);
      ImGui::DragFloat("Width", &m_particleEmitter.size.x, 0.1f, 0, 10.0f);
      ImGui::DragFloat("Height", &m_particleEmitter.size.y, 0.1f, 0, 10.0f);
      ImGui::DragFloat("Speed", &m_particleEmitter.size.x, 0.1f, 0.1f, 10.0f);
      ImGui::TreePop();
    }
    ImGui::SeparatorText("Debug Metrics");
    ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::Text("Alive: %d / %zu", m_particleSystem->aliveCount(), m_particleSystem->capacity());

    const float pct = (float)m_particleSystem->aliveCount() / (float)m_particleSystem->capacity();
    ImGui::ProgressBar(pct, ImVec2(-1, 0), nullptr); // full width
    ImGui::SameLine();
    ImGui::Text(" %.1f%%", pct * 100.0f);

    ImGui::End();
  }
} // namespace Zen
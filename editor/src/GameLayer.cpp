#include "GameLayer.h"
#include "ZEN_Log.h"
#include "ZEN_RenderCommand.h"
#include "ZEN_Renderer.h"
#include "ZEN_Shader.h"
#include "editor/src/QuadBuilder.h"
#include "imgui.h"
#include "inputs/ZEN_KeyCodes.h"
#include <SDL3/SDL_scancode.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <memory>

void GameLayer::onAttach() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  m_camera.setPosition({0, 0, 0});
  m_camera.setOrthographic(-10, 10, -5.625f, 5.625f);

  m_shader         = std::make_shared<Zen::Shader>("data/particle.vert", "data/particle.frag");
  m_particleSystem = std::make_unique<Zen::ParticleSystem>(5000);
  m_quadBuilder.init(m_shader);

  m_player.pos = {0, 0};

  m_player.emitter.pos       = m_player.pos;
  m_player.emitter.size      = {m_player.width, m_player.height};
  m_player.emitter.colour    = m_player.colour;
  m_player.emitter.spawnRate = 60.0f;

  m_player.emitter.props.position    = m_player.pos;
  m_player.emitter.props.velocity    = {0, -1.5f};
  m_player.emitter.props.lifeTime    = 1.0f;
  m_player.emitter.props.sizeBegin   = 1.0f;
  m_player.emitter.props.sizeEnd     = 0.0f;
  m_player.emitter.props.colourBegin = m_player.colour;
  m_player.emitter.props.colourEnd   = {0.5f, 0.5f, 0, 0};

  Zen::ParticleEmitter fire1({-5.0f, 0}, {0.8f, 0.8f}, {1.0f, 0.3f, 0, 1.0f});
  fire1.props.velocity    = {0, 3.0f};
  fire1.props.lifeTime    = 1.5f;
  fire1.props.sizeBegin   = 0.8f;
  fire1.props.sizeEnd     = 0.1f;
  fire1.props.colourBegin = {1.0f, 0.8f, 0.2f, 1.0f};
  fire1.props.colourEnd   = {1.0f, 0.2f, 0, 0};
  fire1.spawnRate         = 50;
  m_emitters.push_back(fire1);

  Zen::ParticleEmitter sparkle({5.0f, 0}, {0.6f, 0.6f}, {0.8f, 0, 1.0f, 1.0f});
  sparkle.props.velocity    = {0, 2.0f};
  sparkle.props.lifeTime    = 2.0f;
  sparkle.props.sizeBegin   = 0.4f;
  sparkle.props.sizeEnd     = 0;
  sparkle.props.colourBegin = {1.0f, 0.5f, 1.0f, 1.0f};
  sparkle.props.colourEnd   = {0.5f, 0, 1.0f, 0};
  sparkle.spawnRate         = 40;
  m_emitters.push_back(sparkle);
}

void GameLayer::onUpdate(Zen::DeltaTime deltaTime) {
  // m_cameraController.onUpdate(deltaTime);

  Zen::RenderCommand::setClearColour({0.1f, 0.1f, 0.1f, 1.0f});
  Zen::RenderCommand::clear();

  const bool jumpPressed = Zen::Input::isKeyPressed(Zen::Key::Space);
  m_player.update(deltaTime, jumpPressed);

  if (m_playerEmitOnJump && m_player.justJumped()) {
    emitJumpBurst();
  }

  if (m_playerEmitTrail) {
    m_particleSystem->updateEmitter(m_player.emitter, deltaTime);
  }
  m_particleSystem->updateEmitters(m_emitters, deltaTime);

  m_particleSystem->update(deltaTime);
  m_particleSystem->upload();

  Zen::Renderer::beginScene(m_camera);

  drawGround();
  drawEmitters();
  drawPlayer();

  Zen::Renderer::submit(m_particleSystem->shader(), m_particleSystem->vao());

  Zen::Renderer::endScene();
}

void GameLayer::onGUIRender() {
  ImGui::Begin("Game Controls");

  ImGui::SeparatorText("Player");
  ImGui::DragFloat2("Position", &m_player.pos[0], 0.1f, -10.0f, 10.0f);
  ImGui::DragFloat("Jump Power", &m_player.jumpImpulse, 0.1f, 0.0f, 20.0f);
  ImGui::DragFloat("Gravity", &m_player.gravity, 0.5f, -50.0f, 0.0f);
  ImGui::ColorEdit4("Color", &m_player.colour[0]);

  ImGui::SeparatorText("Player Particles");
  ImGui::Checkbox("Emit Trail", &m_playerEmitTrail);
  ImGui::Checkbox("Emit on Jump", &m_playerEmitOnJump);
  ImGui::DragFloat("Trail Spawn Rate", &m_player.emitter.spawnRate, 1.0f, 0.0f, 200.0f);
  ImGui::ColorEdit4("Trail Color Start", &m_player.emitter.props.colourBegin[0]);
  ImGui::ColorEdit4("Trail Color End", &m_player.emitter.props.colourEnd[0]);
  ImGui::DragFloat("Trail Life", &m_player.emitter.props.lifeTime, 0.1f, 0.1f, 5.0f);
  ImGui::DragFloat("Trail Size Start", &m_player.emitter.props.sizeBegin, 0.1f, 0.0f, 5.0f);
  ImGui::DragFloat2("Trail Velocity", &m_player.emitter.props.velocity[0], 0.1f, -10.0f, 10.0f);

  if (ImGui::Button("Emit Jump Burst Now")) {
    emitJumpBurst();
  }

  ImGui::SeparatorText("Emitters");
  for (size_t i = 0; i < m_emitters.size(); ++i) {
    ImGui::PushID(static_cast<int>(i));
    if (ImGui::TreeNode("Emitter", "Emitter %zu", i)) {
      ImGui::DragFloat2("Position", &m_emitters[i].pos[0], 0.1f, -10.0f, 10.0f);
      ImGui::DragFloat("Spawn Rate", &m_emitters[i].spawnRate, 1.0f, 0.0f, 200.0f);
      ImGui::ColorEdit4("Color Start", &m_emitters[i].props.colourBegin[0]);
      ImGui::ColorEdit4("Color End", &m_emitters[i].props.colourEnd[0]);
      ImGui::DragFloat("Lifetime", &m_emitters[i].props.lifeTime, 0.1f, 0.1f, 5.0f);
      ImGui::DragFloat("Size Start", &m_emitters[i].props.sizeBegin, 0.1f, 0.0f, 5.0f);
      ImGui::DragFloat("Size End", &m_emitters[i].props.sizeEnd, 0.1f, 0.0f, 5.0f);
      ImGui::DragFloat2("Velocity", &m_emitters[i].props.velocity[0], 0.1f, -10.0f, 10.0f);

      m_emitters[i].props.position = m_emitters[i].pos;

      ImGui::TreePop();
    }
    ImGui::PopID();
  }

  ImGui::SeparatorText("Particle System");
  ImGui::Text("Particles: %d / %zu",
              static_cast<int>(m_particleSystem->capacity()),
              m_particleSystem->capacity());

  if (ImGui::Button("Clear All Particles")) {
    m_particleSystem->clear();
  }

  ImGui::SeparatorText("Ground");
  ImGui::DragFloat2("Ground Position", &m_groundPos[0], 0.1f, -20.0f, 20.0f);
  ImGui::DragFloat2("Ground Size", &m_groundSize[0], 0.1f, 0.0f, 50.0f);
  ImGui::ColorEdit4("Ground Color", &m_groundColour[0]);

  ImGui::End();
}

void GameLayer::emitJumpBurst() {
  const int burstCount = 30;
  for (int i = 0; i < burstCount; ++i) {
    Zen::ParticleProps p;
    p.position = m_player.pos;

    float angle = glm::linearRand(0.0f, glm::two_pi<float>());
    float speed = glm::linearRand(3.0f, 6.0f);
    p.velocity  = {glm::cos(angle) * speed, glm::sin(angle) * speed};

    p.lifeTime    = 0.6f;
    p.sizeBegin   = 0.5f;
    p.sizeEnd     = 0.0f;
    p.colourBegin = {1.0f, 1.0f, 0.3f, 1.0f};
    p.colourEnd   = {1.0f, 0.5f, 0.0f, 0.0f};

    m_particleSystem->emit(p);
  }
}

void GameLayer::drawPlayer() {
  m_quadBuilder.drawQuad(m_player.pos, {m_player.width, m_player.height}, m_player.colour);
}

void GameLayer::drawEmitters() {
  for (const auto &emitter : m_emitters) {
    m_quadBuilder.drawQuad(emitter.pos, emitter.size, emitter.colour);
  }
}

void GameLayer::drawGround() { m_quadBuilder.drawQuad(m_groundPos, m_groundSize, m_groundColour); }
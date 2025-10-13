#pragma once
#include "Player.h"
#include "editor/src/QuadBuilder.h"
#include <memory>
#include <particles/ZEN_ParticleSystem.h>
#include <time/ZEN_DeltaTime.h>
#include <zen/camera/ZEN_Camera.h>
#include <zen/camera/ZEN_CameraController.h>
#include <zen/events/ZEN_Event.h>
#include <zen/inputs/ZEN_Input.h>
#include <zen/layer/ZEN_Layer.h>
#include <zen/renderer/ZEN_Buffer.h>
#include <zen/renderer/ZEN_RenderCommand.h>
#include <zen/renderer/ZEN_Renderer.h>
#include <zen/renderer/ZEN_Shader.h>
#include <zen/renderer/ZEN_VertexArray.h>

using namespace Zen;

class GameLayer final : public Layer {
public:
  GameLayer() : Layer(49), m_camera(CameraType::Orthographic), m_cameraController(m_camera) {}

  void onAttach() override;
  void onUpdate(DeltaTime deltaTime) override;
  bool onEvent(const ZenEvent &event) override { return false; }
  void onGUIRender() override;

private:
  void drawPlayer();
  void drawEmitters();
  void drawGround();
  void emitJumpBurst();

  Camera m_camera;
  CameraController m_cameraController;
  std::unique_ptr<ParticleSystem> m_particleSystem;

  Player m_player;
  std::vector<ParticleEmitter> m_emitters;

  std::shared_ptr<Shader> m_shader;
  QuadBuilder m_quadBuilder;

  bool m_playerEmitOnJump = true;
  bool m_playerEmitTrail  = true;

  glm::vec2 m_groundSize   = {20.0f, (5.625f * 2)};
  glm::vec2 m_groundPos    = {0, -5.625f};
  glm::vec4 m_groundColour = {0.25f, 0.25f, 0.2f, 1.0f};

};
#pragma once
#include "Player.h"
#include "editor/src/Obstacle.h"
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

enum class GameState { Playing, GameOver, Paused };

class GameLayer final : public Layer {
public:
  GameLayer() : Layer(49), m_camera(CameraType::Orthographic), m_cameraController(m_camera) {}

  void onAttach() override;
  void onUpdate(DeltaTime deltaTime) override;
  bool onEvent(const ZenEvent &event) override { return false; }
  void onGUIRender() override;

private:
  void drawPlayer();
  void drawGround();
  void emitJumpBurst();
  void emitCollisionEffect();
  void drawObstacles();
  void drawUI();
  void updateGame(DeltaTime deltaTime);
  void updateGamePaused(DeltaTime deltaTime);
  void updateGameOver(DeltaTime deltaTime);
  void spawnObstacle();
  void checkCollisions();
  void restartGame();

  Camera m_camera;
  CameraController m_cameraController;
  std::unique_ptr<ParticleSystem> m_particleSystem;

  Player m_player;
  std::vector<Obstacle> m_obstacles;

  std::shared_ptr<Shader> m_shader;
  QuadBuilder m_quadBuilder;

  bool m_playerEmitTrail   = true;
  bool m_obstacleEmitTrail = true;
  bool m_emitJumpBurst     = true;

  glm::vec2 m_groundSize   = {30.0f, (5.625f * 2)};
  glm::vec2 m_groundPos    = {0, -5.625f};
  glm::vec4 m_groundColour = {0.2f, 0.2f, 0.18f, 1.0f};

  GameState m_gameState = GameState::Playing;
  float m_score         = 0.0f;
  float m_highScore     = 0.0f;
  float m_gameSpeed     = 1.0f;

  float m_spawnTimer        = 0.0f;
  float m_spawnInterval     = 2.0f;
  float m_minSpawnInterval  = 0.8f;
  float m_speedIncreaseRate = 0.05f;

  int m_nextObstacleIndex = 0;

  ObstacleType getRandomObstacleType();
};
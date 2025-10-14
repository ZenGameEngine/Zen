#include "GameLayer.h"
#include "ZEN_Event.h"
#include "ZEN_Log.h"
#include "ZEN_RenderCommand.h"
#include "ZEN_Renderer.h"
#include "ZEN_Shader.h"
#include "camera/ZEN_CameraController.h"
#include "editor/src/Obstacle.h"
#include "editor/src/QuadBuilder.h"
#include "imgui.h"
#include "inputs/ZEN_KeyCodes.h"
#include "time/ZEN_DeltaTime.h"
#include <SDL3/SDL_scancode.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <memory>

using namespace Zen;

void GameLayer::onAttach() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  m_camera.setPosition({0, 0, 0});
  m_camera.setOrthographic(-10, 10, -5.625f, 5.625f);
  m_cameraController.setWorldBounds(-10.0f, 10.0f, -5.625f, 5.625f);
  m_cameraController.enableWorldBounds(true);

  m_shader         = std::make_shared<Shader>("data/particle.vert", "data/particle.frag");
  m_particleSystem = std::make_unique<ParticleSystem>(5000);
  m_quadBuilder.init(m_shader);

  m_player.pos = {-7.0f, 0};

  m_player.emitter.pos       = m_player.pos;
  m_player.emitter.size      = {m_player.width, m_player.height};
  m_player.emitter.colour    = m_player.colour;
  m_player.emitter.spawnRate = 80.0f;

  m_player.emitter.props.position    = m_player.pos;
  m_player.emitter.props.velocity    = {-5.0f, 0};
  m_player.emitter.props.lifeTime    = 0.6f;
  m_player.emitter.props.sizeBegin   = 0.4f;
  m_player.emitter.props.sizeEnd     = 0;
  m_player.emitter.props.colourBegin = {1.f, 0, 0, 1.0f};
  m_player.emitter.props.colourEnd   = {0.1f, 0.4f, 0.2f, 0};
  m_player.emitter.vRand.coneDeg     = 30.0f;
  m_player.emitter.vRand.speedMinMul = 0.5f;
  m_player.emitter.vRand.speedMaxMul = 2.0f;
  m_player.emitter.vRand.noiseSigma  = 1.0f;

  for (int i = 0; i < 10; ++i) {
    m_obstacles.emplace_back(ObstacleType::SmallBox, 50.0f);
    m_obstacles[i].active = false;
  }
}

void GameLayer::onUpdate(DeltaTime deltaTime) {
  m_cameraController.onUpdate(deltaTime);

  RenderCommand::setClearColour({0.1f, 0.1f, 0.1f, 1.0f});
  RenderCommand::clear();

  if (m_gameState == GameState::Playing) {
    updateGame(deltaTime);
  } else if (m_gameState == GameState::GameOver) {
    updateGameOver(deltaTime);
  } else if (m_gameState == GameState::Paused) {
    updateGamePaused(deltaTime);
  }

  m_particleSystem->update(deltaTime);
  m_particleSystem->upload();

  Renderer::beginScene(m_camera);

  drawGround();
  drawObstacles();
  drawPlayer();

  Renderer::submit(m_particleSystem->shader(), m_particleSystem->vao());

  Renderer::endScene();

  drawUI();
}
bool GameLayer::onEvent(const ZenEvent &event) {
  m_cameraController.onEvent(event);
  if (event.header.type == EventType::WindowResize) {
    RenderCommand::setViewport(event.windowResize.width, event.windowResize.height);
    ZEN_LOG_TRACE("resize viewport");
  }
  return false;
}

void GameLayer::updateGame(DeltaTime deltaTime) {
  if (Input::isKeyPressed(Key::P)) {
    m_gameState = GameState::Paused;
    return;
  }
  const bool jumpPressed = Input::isKeyPressed(Key::Space);
  m_player.update(deltaTime, jumpPressed);

  if (m_emitJumpBurst && m_player.justJumped()) {
    emitJumpBurst();
  }
  if (m_playerEmitTrail) {
    m_particleSystem->updateEmitter(m_player.emitter, deltaTime);
  }

  m_gameSpeed += m_speedIncreaseRate * deltaTime.seconds();
  m_gameSpeed = glm::min(m_gameSpeed, 3.0f);

  for (auto &obstacle : m_obstacles) {
    if (obstacle.active) {

      float originalSpeed = obstacle.speed;
      obstacle.speed      = originalSpeed * m_gameSpeed;
      obstacle.update(deltaTime);

      if (m_obstacleEmitTrail) {
        m_particleSystem->updateEmitter(obstacle.emitter, deltaTime);
      }

      obstacle.speed = originalSpeed;
    }
  }

  m_spawnTimer += deltaTime.seconds();
  if (m_spawnTimer >= m_spawnInterval) {
    spawnObstacle();
    m_spawnTimer = 0;

    m_spawnInterval = glm::max(m_spawnInterval - 0.05f, m_minSpawnInterval);
  }

  checkCollisions();

  m_score += deltaTime.seconds() * m_gameSpeed * 5.0f;
}

void GameLayer::updateGamePaused(DeltaTime deltaTime) {
  if (Input::isKeyPressed(Key::P) || Input::isKeyPressed(Key::Space)) {
    m_gameState = GameState::Playing;
    return;
  }

  for (auto &obstacle : m_obstacles) {
    if (obstacle.active && m_obstacleEmitTrail) {
      m_particleSystem->updateEmitter(obstacle.emitter, deltaTime);
    }
  }
}
void GameLayer::updateGameOver(DeltaTime deltaTime) {

  if (Input::isKeyPressed(Key::R) || Input::isKeyPressed(Key::Space)) {
    restartGame();
  }

  for (auto &obstacle : m_obstacles) {
    if (obstacle.active && m_obstacleEmitTrail) {
      m_particleSystem->updateEmitter(obstacle.emitter, deltaTime);
    }
  }
}

void GameLayer::spawnObstacle() {
  Obstacle *obstacle = nullptr;
  for (auto &obs : m_obstacles) {
    if (!obs.active) {
      obstacle = &obs;
      break;
    }
  }

  if (!obstacle) {
    obstacle            = &m_obstacles[m_nextObstacleIndex];
    m_nextObstacleIndex = (m_nextObstacleIndex + 1) % m_obstacles.size();
  }

  ObstacleType type = getRandomObstacleType();
  *obstacle         = Obstacle(type, 12.0f);
  obstacle->active  = true;

  ZEN_LOG_TRACE("Spawned obstacle of type {}", static_cast<int>(type));
}

void GameLayer::checkCollisions() {
  for (auto &obstacle : m_obstacles) {
    if (obstacle.active && obstacle.collidesWith(m_player.pos, m_player.getSize())) {

      ZEN_LOG_INFO("Collision detected! Game Over!");
      m_gameState = GameState::GameOver;

      if (m_score > m_highScore) {
        m_highScore = m_score;
        ZEN_LOG_INFO("New high score: {}", m_highScore);
      }

      emitCollisionEffect();
      break;
    }
  }
}

void GameLayer::restartGame() {
  ZEN_LOG_INFO("Restarting game...");

  m_gameState     = GameState::Playing;
  m_score         = 0;
  m_gameSpeed     = 1.0f;
  m_spawnTimer    = 0;
  m_spawnInterval = 2.0f;

  m_player.pos = {-7.0f, 0};
  m_player.vy  = 0;

  for (auto &obstacle : m_obstacles) {
    obstacle.active = false;
  }

  m_particleSystem->clear();
}

void GameLayer::emitJumpBurst() {
  const int burstCount = 30;
  for (int i = 0; i < burstCount; ++i) {
    ParticleProps p;
    p.position = m_player.pos;

    float angle = glm::linearRand(0.0f, glm::two_pi<float>());
    float speed = glm::linearRand(3.0f, 6.0f);
    p.velocity  = {glm::cos(angle) * speed, glm::sin(angle) * speed};

    p.lifeTime    = 0.6f;
    p.sizeBegin   = 0.5f;
    p.sizeEnd     = 0;
    p.colourBegin = {1.0f, 1.0f, 0.3f, 1.0f};
    p.colourEnd   = {1.0f, 0.5f, 0, 0};

    m_particleSystem->emit(p);
  }
}

void GameLayer::emitCollisionEffect() {
  const int explosionCount = 100;
  for (int i = 0; i < explosionCount; ++i) {
    ParticleProps explosion;
    explosion.position = m_player.pos;

    // Explosion in all directions
    float angle        = glm::linearRand(0.0f, glm::two_pi<float>());
    float speed        = glm::linearRand(3.0f, 10.0f);
    explosion.velocity = {glm::cos(angle) * speed, glm::sin(angle) * speed};

    explosion.lifeTime    = 1.0f;
    explosion.sizeBegin   = 0.6f;
    explosion.sizeEnd     = 0;
    explosion.colourBegin = {1.0f, 0.3f, 0.1f, 1.0f};
    explosion.colourEnd   = {0.5f, 0.1f, 0, 0};

    m_particleSystem->emit(explosion);
  }
}

ObstacleType GameLayer::getRandomObstacleType() {
  int random = rand() % 100;

  if (random < 40) {
    return ObstacleType::SmallBox;
  }
  if (random < 75) {
    return ObstacleType::TallBox;
  }
  return ObstacleType::FlyingBox;
}

void GameLayer::drawPlayer() {
  glm::vec4 colour = m_player.colour;
  if (m_gameState == GameState::GameOver) {
    colour = {0.5f, 0.5f, 0.5f, 1.0f};
  }
  m_quadBuilder.drawQuad(m_player.pos, m_player.getSize(), colour);
}

void GameLayer::drawObstacles() {
  for (const auto &obstacle : m_obstacles) {
    if (obstacle.active) {
      m_quadBuilder.drawQuad(obstacle.pos, obstacle.size, obstacle.colour);
    }
  }
}

void GameLayer::drawGround() { m_quadBuilder.drawQuad(m_groundPos, m_groundSize, m_groundColour); }

void GameLayer::drawUI() {
  ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
  ImGui::SetNextWindowBgAlpha(0.6f);
  ImGui::Begin("Score",
               nullptr,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                   ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);

  ImGui::Text("Score: %.0f", m_score);
  ImGui::Text("High: %.0f", m_highScore);
  ImGui::Text("Speed: %.1fx", m_gameSpeed);

  if (m_gameState == GameState::GameOver) {
    ImGui::Separator();
    ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "GAME OVER!");
    ImGui::Text("Press R or SPACE to restart");
  }

  if (m_gameState == GameState::Paused) {
    ImGui::Separator();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "PAUSED!");
    ImGui::Text("Press P or SPACE to Resume");
  }

  ImGui::End();
}

void GameLayer::onGUIRender() {
  ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiCond_Once);
  ImGui::SetNextWindowPos(ImVec2(800, 10), ImGuiCond_Once);
  ImGui::Begin("Editor");

  ImGui::SeparatorText("Game State");

  const char *stateNames[] = {"Playing", "GameOver", "Paused"};
  ImGui::Text("State: %s", stateNames[static_cast<int>(m_gameState)]);
  ImGui::Text("Score: %.0f", m_score);
  ImGui::Text("High Score: %.0f", m_highScore);

  if (ImGui::Button("Restart Game (R)")) {
    restartGame();
  }
  ImGui::SameLine();
  if (m_gameState == GameState::Playing) {
    if (ImGui::Button("Pause Game (P)")) {
      m_gameState = GameState::Paused;
    }
  } else if(m_gameState == GameState::Paused){
     if (ImGui::Button("Resume Game (P)")) {
      m_gameState = GameState::Playing;
    }
  }
  ImGui::SameLine();
  if (ImGui::Button("Spawn Obstacle")) {
    spawnObstacle();
  }

  ImGui::SeparatorText("Difficulty");
  ImGui::DragFloat("Game Speed", &m_gameSpeed, 0.1f, 0.5f, 5.0f);
  ImGui::DragFloat("Speed Increase Rate", &m_speedIncreaseRate, 0.01f, 0, 1.0f);
  ImGui::DragFloat("Spawn Interval", &m_spawnInterval, 0.1f, 0.5f, 5.0f);
  ImGui::DragFloat("Min Spawn Interval", &m_minSpawnInterval, 0.1f, 0.3f, 2.0f);

  ImGui::SeparatorText("Player");
  ImGui::DragFloat("Jump Power", &m_player.jumpImpulse, 0.1f, 5.0f, 20.0f);
  ImGui::DragFloat("Gravity", &m_player.gravity, 0.5f, -50.0f, -5.0f);
  ImGui::DragFloat2("Player Size", &m_player.width, 0.1f, 0.1f, 3.0f);
  ImGui::ColorEdit4("Player Colour", &m_player.colour[0]);

  ImGui::SeparatorText("Player Particles");
  ImGui::Checkbox("Emit Trail", &m_playerEmitTrail);
  ImGui::Checkbox("Emit Jump Burst", &m_emitJumpBurst);
  ImGui::DragFloat("Trail Spawn Rate", &m_player.emitter.spawnRate, 1.0f, 0, 200.0f);
  ImGui::DragFloat2("Trail Velocity", &m_player.emitter.props.velocity[0], 0.1f, -10.0f, 10.0f);
  ImGui::ColorEdit4("Trail Colour Start", &m_player.emitter.props.colourBegin[0]);
  ImGui::ColorEdit4("Trail Colour End", &m_player.emitter.props.colourEnd[0]);
  ImGui::DragFloat("Trail Life", &m_player.emitter.props.lifeTime, 0.1f, 0.1f, 3.0f);
  ImGui::DragFloat("Cone (deg)", &m_player.emitter.vRand.coneDeg, 0.1f, 0, 60.0f);
  ImGui::DragFloat("Speed min x", &m_player.emitter.vRand.speedMinMul, 0.01f, 0, 2.0f);
  ImGui::DragFloat("Speed max x", &m_player.emitter.vRand.speedMaxMul, 0.01f, 0, 3.0f);
  ImGui::DragFloat("Noise sigma", &m_player.emitter.vRand.noiseSigma, 0.01f, 0, 1.0f);

  ImGui::SeparatorText("Obstacles");
  ImGui::Checkbox("Emit Obstacle Trails", &m_obstacleEmitTrail);

  int activeCount = 0;
  for (const auto &obs : m_obstacles) {
    if (obs.active) {
      activeCount++;
    }
  }
  ImGui::Text("Active Obstacles: %d / %zu", activeCount, m_obstacles.size());

  if (ImGui::Button("Clear All Obstacles")) {
    for (auto &obs : m_obstacles) {
      obs.active = false;
    }
  }

  if (ImGui::TreeNode("Obstacle Types")) {
    for (size_t i = 0; i < m_obstacles.size() && i < 5; ++i) {
      ImGui::PushID(static_cast<int>(i));
      if (m_obstacles[i].active) {
        const char *typeNames[] = {"Small", "Tall", "Flying"};
        ImGui::Text("Obstacle %zu: %s (%.1f, %.1f)",
                    i,
                    typeNames[static_cast<int>(m_obstacles[i].type)],
                    m_obstacles[i].pos.x,
                    m_obstacles[i].pos.y);
      }
      ImGui::PopID();
    }
    ImGui::TreePop();
  }

  ImGui::SeparatorText("Test Spawns");
  if (ImGui::Button("Spawn Small Box")) {
    m_obstacles.push_back(Obstacle(ObstacleType::SmallBox, 12.0f));
  }
  if (ImGui::Button("Spawn Tall Box")) {
    m_obstacles.push_back(Obstacle(ObstacleType::TallBox, 12.0f));
  }
  if (ImGui::Button("Spawn Flying Box")) {
    m_obstacles.push_back(Obstacle(ObstacleType::FlyingBox, 12.0f));
  }

  ImGui::SeparatorText("Particle System");
  ImGui::Text("Particles: %zu", m_particleSystem->capacity());
  if (ImGui::Button("Clear All Particles")) {
    m_particleSystem->clear();
  }

  ImGui::End();
}
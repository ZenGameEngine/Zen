#pragma once
#include <glm/glm.hpp>
#include <particles/ZEN_ParticleSystem.h>
#include <zen/time/ZEN_DeltaTime.h>

class Player {
public:
  glm::vec2 pos{0.0f, 0.0f};
  float vy = 0.0f;

  float gravity    = -50.0f; // units/s^2
  float jumpPower  = 18.0f;  // units/s
  float width      = 1.0f;
  float height     = 1.0f;
  glm::vec4 colour = {1.0f, 0.0f, 0.0f, 1.0f};

  Zen::ParticleEmitter emitter{
      {0, 0},
      {1, 1},
      {1, 1, 1, 1}
  };

  bool onGround() const;
  void update(Zen::DeltaTime deltaTime, bool jumpPressed);

  bool wasOnGround() const { return m_wasOnGround; }
  bool justJumped() const { return m_justJumped; }
  glm::vec2 getSize() const { return {width, height}; }

private:
  bool m_wasOnGround = true;
  bool m_justJumped  = false;
};
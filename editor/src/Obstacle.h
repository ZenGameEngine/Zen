#pragma once
#include "particles/ZEN_ParticleSystem.h"
#include <glm/glm.hpp>
#include <zen/time/ZEN_DeltaTime.h>

enum class ObstacleType {
  SmallBox, 
  TallBox, 
  FlyingBox 
};

class Obstacle {
public:
  glm::vec2 pos{12.0f, 0.0f}; 
  glm::vec2 size{1.0f, 1.0f};
  glm::vec4 colour{1.0f, 0.5f, 0.0f, 1.0f};

  ObstacleType type = ObstacleType::SmallBox;
  float speed       = 5.0f; // units/s
  bool active       = true;

  Zen::ParticleEmitter emitter{
      {0, 0},
      {1, 1},
      {1, 1, 1, 1}
  };

  Obstacle(ObstacleType t, float x = 12.0f);

  void update(Zen::DeltaTime dt);
  void reset(float x = 12.0f);

  // Simple AABB collision
  bool collidesWith(const glm::vec2 &otherPos, const glm::vec2 &otherSize) const;

  // Get bottom Y position (for ground vs flying)
  float getBottomY() const { return pos.y - size.y * 0.5f; }
};
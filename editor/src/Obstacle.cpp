#include "Obstacle.h"

Obstacle::Obstacle(ObstacleType t, float x) : type(t), pos{x, 0.0f} {
  switch (type) {
    case ObstacleType::SmallBox:
      size   = {0.8f, 0.8f};
      pos.y  = 0.0f;
      colour = {1.0f, 0.5f, 0.0f, 1.0f};
      speed  = 6.0f;
      break;

    case ObstacleType::TallBox:
      size   = {0.6f, 2.0f};
      pos.y  = 1.0f;
      colour = {1.0f, 0.2f, 0.2f, 1.0f};
      speed  = 5.5f;
      break;

    case ObstacleType::FlyingBox:
      size   = {1.0f, 0.6f};
      pos.y  = 2.5f;
      colour = {0.5f, 0.2f, 1.0f, 1.0f};
      speed  = 7.0f;
      break;
  }

  emitter.pos       = pos;
  emitter.size      = size;
  emitter.colour    = colour;
  emitter.spawnRate = 40.0f;

  emitter.props.position    = pos;
  emitter.props.velocity    = {3.0f, 0.0f};
  emitter.props.lifeTime    = 0.8f;
  emitter.props.sizeBegin   = 0.3f;
  emitter.props.sizeEnd     = 0.0f;
  emitter.props.colourBegin = colour;
  emitter.props.colourEnd   = glm::vec4(colour.r, colour.g, colour.b, 0.0f);
}

void Obstacle::update(Zen::DeltaTime dt) {
  if (!active) {
    return;
  }

  pos.x -= speed * dt.seconds();

  emitter.pos            = pos;
  emitter.props.position = pos;

  if (pos.x < -12.0f) {
    active = false;
  }
}

void Obstacle::reset(float x) {
  pos.x  = x;
  active = true;

  switch (type) {
    case ObstacleType::SmallBox:
      pos.y = 0.0f;
      break;
    case ObstacleType::TallBox:
      pos.y = 1.0f;
      break;
    case ObstacleType::FlyingBox:
      pos.y = 2.5f;
      break;
  }

  emitter.pos            = pos;
  emitter.props.position = pos;
}

bool Obstacle::collidesWith(const glm::vec2 &otherPos, const glm::vec2 &otherSize) const {
  if (!active) {
    return false;
  }

  // simple AABB collision
  float left1   = pos.x - (size.x * 0.5f);
  float right1  = pos.x + (size.x * 0.5f);
  float bottom1 = pos.y - (size.y * 0.5f);
  float top1    = pos.y + (size.y * 0.5f);

  float left2   = otherPos.x - (otherSize.x * 0.5f);
  float right2  = otherPos.x + (otherSize.x * 0.5f);
  float bottom2 = otherPos.y - (otherSize.y * 0.5f);
  float top2    = otherPos.y + (otherSize.y * 0.5f);

  return !(left1 > right2 || right1 < left2 || bottom1 > top2 || top1 < bottom2);
}
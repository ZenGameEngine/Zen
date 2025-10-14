#include "Player.h"

bool Player::onGround() const { return pos.y <= 0.0f; }

void Player::update(Zen::DeltaTime deltaTime, bool jumpPressed) {
  m_wasOnGround = onGround();
  m_justJumped  = false;

  if (jumpPressed && onGround()) {
    vy           = jumpPower;
    m_justJumped = true;
    ZEN_LOG_TRACE("Jumped");
  }

  vy += gravity * deltaTime.seconds();
  pos.y += vy * deltaTime.seconds();

  if (pos.y < 0.0f) {
    pos.y = 0.0f;
    vy    = 0.0f;
  }

  emitter.pos            = pos;
  emitter.props.position = pos;
}
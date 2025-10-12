#pragma once

namespace Zen {
  class DeltaTime {
  public:
    DeltaTime(float time = 0.0f) : m_time(time) {}

    operator float() const { return m_time; } // always returns a float if just called by itself

    // these are just for clarification and ease of life
    float seconds() const { return m_time; }
    float milliseconds() const { return m_time * 1000.0f; }

  private:
    float m_time = 0.0f;
  };
} // namespace Zen
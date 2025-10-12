#pragma once

#include <chrono>

namespace Zen {
  class Timer {
  public:
    Timer() { restart(); }

    void restart() { m_start = std::chrono::steady_clock::now(); }

    float duration() {
      return std::chrono::duration<float>(std::chrono::steady_clock::now() - m_start).count();
    }

    float durationMilliseconds() {
      return std::chrono::duration<float, std::milli>(std::chrono::steady_clock::now() - m_start)
          .count();
    }

  private:
    std::chrono::time_point<std::chrono::steady_clock> m_start;
  };
} // namespace Zen
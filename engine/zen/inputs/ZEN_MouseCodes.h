#pragma once

#include <zen/zen_pch.h>

namespace Zen {
  enum class MouseButton : uint8_t { None = 0, Left = 1, Middle = 2, Right = 3, X1 = 4, X2 = 5 };
  enum class MouseButtonState : uint32_t {
    None   = 0,
    Left   = 1 << 0,
    Middle = 1 << 1,
    Right  = 1 << 2,
    X1     = 1 << 3,
    X2     = 1 << 4
  };

  constexpr MouseButtonState operator|(MouseButtonState a, MouseButtonState b) {
    return static_cast<MouseButtonState>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
  }

  constexpr MouseButtonState operator&(MouseButtonState a, MouseButtonState b) {
    return static_cast<MouseButtonState>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
  }

  constexpr MouseButtonState &operator|=(MouseButtonState &a, MouseButtonState b) {
    a = a | b;
    return a;
  }

  constexpr MouseButtonState mapSDLMouseStates(SDL_MouseButtonFlags currentState) {
    MouseButtonState states = MouseButtonState::None;

    if (currentState & SDL_BUTTON_LMASK)
      states |= MouseButtonState::Left;
    if (currentState & SDL_BUTTON_MMASK)
      states |= MouseButtonState::Middle;
    if (currentState & SDL_BUTTON_RMASK)
      states |= MouseButtonState::Right;
    if (currentState & SDL_BUTTON_X1MASK)
      states |= MouseButtonState::X1;
    if (currentState & SDL_BUTTON_X2MASK)
      states |= MouseButtonState::X2;

    return states;
  }
} // namespace Zen

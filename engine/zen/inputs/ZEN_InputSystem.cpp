#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>
#include <zen/inputs/ZEN_InputSystem.h>

namespace Zen {
  void InputSystem::begin() { m_currKeyboard = SDL_GetKeyboardState(nullptr); }

  void InputSystem::end() {
    std::memcpy(m_prev.data(), m_currKeyboard, SDL_SCANCODE_COUNT * sizeof(bool));
  }

  void InputSystem::reset() {
    SDL_ResetKeyboard();
    m_prev.fill(0);
  }

  bool InputSystem::held(int scancode) const {
    return (m_currKeyboard && m_currKeyboard[scancode]);
  }
  bool InputSystem::pressed(int scancode) const {
    return m_currKeyboard && (m_currKeyboard[scancode] && !m_prev[scancode]);
  }
  bool InputSystem::released(int scancode) const {
    return m_currKeyboard && (!m_currKeyboard[scancode] && m_prev[scancode]);
  }

} // namespace Zen
#include <zen/inputs/ZEN_Input.h>
#include <zen/inputs/ZEN_KeyCodes.h>

namespace Zen {

  const InputSystem *Input::s_inputSystem = nullptr;

  void Input::bind(const InputSystem *inputSystem) { s_inputSystem = inputSystem; }

  void Input::unbind() { s_inputSystem = nullptr; }

  bool Input::isKeyHeld(ScanCode scancode) {
    return s_inputSystem->held(static_cast<int>(scancode));
  }

  bool Input::isKeyPressed(ScanCode scancode) {
    return s_inputSystem->pressed(static_cast<int>(scancode));
  }

  bool Input::isKeyReleased(ScanCode scancode) {
    return s_inputSystem->released(static_cast<int>(scancode));
  }
} // namespace Zen
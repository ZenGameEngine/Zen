#pragma once

#include <zen/inputs/ZEN_InputSystem.h>
#include <zen/inputs/ZEN_KeyCodes.h>
#include <zen/zen_pch.h>

namespace Zen {
  class Input {
  public:
    static void bind(const InputSystem *inputSystem);
    static void unbind();
    static bool isKeyHeld(ScanCode scancode);
    static bool isKeyPressed(ScanCode scancode);
    static bool isKeyReleased(ScanCode scancode);

  private:
    static const InputSystem *s_inputSystem;
  };
} // namespace Zen
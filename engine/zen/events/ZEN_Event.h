#pragma once

#include <zen/zen_pch.h>

#include <zen/inputs/ZEN_KeyCodes.h>
#include <zen/inputs/ZEN_MouseCodes.h>

namespace Zen {
  enum class EventType : uint8_t {
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
    TextInput,
    Quit
  };

  enum class EventCategory : uint32_t {
    None        = 0,
    Application = 1 << 0,
    Input       = 1 << 1,
    Keyboard    = 1 << 2,
    Mouse       = 1 << 3,
    Text        = 1 << 4
  };

  constexpr EventCategory operator|(EventCategory a, EventCategory b) {
    return EventCategory((uint32_t)a | (uint32_t)b);
  }

  constexpr EventCategory operator&(EventCategory a, EventCategory b) {
    return EventCategory((uint32_t)a & (uint32_t)b);
  }

  constexpr bool any(EventCategory c, EventCategory mask) {
    return ((uint32_t)c & (uint32_t)mask) != 0;
  }

  // FOR EVENT TYPE PAYLOAD STUFF
  struct EventHeader {
    EventType type;
    EventCategory category;
  };

  struct WindowResize {
    int width, height;
  };

  struct WindowMoved {
    int x, y;
  };

  struct KeyPayload {
    ScanCode scancode;
    bool repeat;
    KeyModifier mods;
  };

  struct MouseMovePayload {
    float x, y, dx, dy;
    MouseButtonState state;
  };

  struct MouseButtonPayload {
    MouseButton button;
    uint8_t clicks;
    float x, y;
  };

  struct MouseWheelPayload {
    float x, y, pos_x, pos_y;
    int scrl_length, scrl_height;
  };

  struct TextInputPayload {
    char32_t codepoint;
  };

  struct ZenEvent {
    EventHeader header;
    union {
      WindowResize windowResize;
      WindowMoved windowMoved;
      KeyPayload key;
      MouseMovePayload mouseMove;
      MouseButtonPayload mouseButton;
      MouseWheelPayload mouseWheel;
      TextInputPayload textInput;
    };
  };

  ZenEvent TranslateEvent(const SDL_Event &e);
} // namespace Zen

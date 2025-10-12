#include <zen/events/ZEN_Event.h>

namespace Zen {

  static ZenEvent TranslateWindowEvent(const SDL_Event &e) {
    ZenEvent event{};
    event.header.category = EventCategory::Application;

    switch (e.type) {
      case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        event.header.type = EventType::WindowClose;
        break;

      case SDL_EVENT_WINDOW_RESIZED:
        event.header.type         = EventType::WindowResize;
        event.windowResize.width  = e.window.data1;
        event.windowResize.height = e.window.data2;
        break;

      case SDL_EVENT_WINDOW_FOCUS_GAINED:
        event.header.type = EventType::WindowFocus;
        break;

      case SDL_EVENT_WINDOW_FOCUS_LOST:
        event.header.type = EventType::WindowLostFocus;
        break;

      case SDL_EVENT_WINDOW_MOVED:
        event.header.type   = EventType::WindowMoved;
        event.windowMoved.x = e.window.data1;
        event.windowMoved.y = e.window.data2;
        break;

      default:
        event.header.type = EventType::None;
        break;
    }

    return event;
  }

  static ZenEvent TranslateKeyEvent(const SDL_Event &e) {
    ZenEvent event{};
    event.header.category = EventCategory::Input | EventCategory::Keyboard;

    if (e.type == SDL_EVENT_KEY_DOWN) {
      event.header.type = EventType::KeyPressed;
      event.key.repeat  = e.key.repeat;
    } else {
      event.header.type = EventType::KeyReleased;
    }

    event.key.scancode = e.key.scancode;
    event.key.mods     = mapSDLMods(e.key.mod);

    return event;
  }

  static ZenEvent TranslateMouseEvent(const SDL_Event &e) {
    ZenEvent event{};
    event.header.category = EventCategory::Input | EventCategory::Mouse;

    switch (e.type) {
      case SDL_EVENT_MOUSE_MOTION:
        event.header.type     = EventType::MouseMoved;
        event.mouseMove.state = mapSDLMouseStates(e.motion.state);
        event.mouseMove.x     = e.motion.x;
        event.mouseMove.y     = e.motion.y;
        event.mouseMove.dx    = e.motion.xrel;
        event.mouseMove.dy    = e.motion.yrel;
        break;

      case SDL_EVENT_MOUSE_BUTTON_DOWN:
      case SDL_EVENT_MOUSE_BUTTON_UP:
        event.header.type = (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
                                ? EventType::MouseButtonPressed
                                : EventType::MouseButtonReleased;

        event.mouseButton.button = static_cast<MouseButton>(e.button.button);
        event.mouseButton.clicks = e.button.clicks;
        event.mouseButton.x      = e.button.x;
        event.mouseButton.y      = e.button.y;
        break;

      case SDL_EVENT_MOUSE_WHEEL:
        event.header.type = EventType::MouseScrolled;

        event.mouseWheel.x           = e.wheel.x;
        event.mouseWheel.y           = e.wheel.y;
        event.mouseWheel.pos_x       = e.wheel.mouse_x;
        event.mouseWheel.pos_y       = e.wheel.mouse_y;
        event.mouseWheel.scrl_length = e.wheel.integer_x;
        event.mouseWheel.scrl_height = e.wheel.integer_y;
        break;

      default:
        event.header.type = EventType::None;
        break;
    }

    return event;
  }

  static void *utf8_decode(void *buf, uint32_t *c, int *e) { // Thank you Chris Wellons
    static const char lengths[]  = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                    0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 4, 0};
    static const int masks[]     = {0x00, 0x7f, 0x1f, 0x0f, 0x07};
    static const uint32_t mins[] = {4194304, 0, 128, 2048, 65536};
    static const int shiftc[]    = {0, 18, 12, 6, 0};
    static const int shifte[]    = {0, 6, 4, 2, 0};

    unsigned char *s = static_cast<unsigned char *>(buf);
    ;
    int len = static_cast<unsigned char>(lengths[s[0] >> 3]);

    /* Compute the pointer to the next character early so that the next
     * iteration can start working on the next character. Neither Clang
     * nor GCC figure out this reordering on their own.
     */
    unsigned char *next = s + len + !len;

    /* Assume a four-byte character and load four bytes. Unused bits are
     * shifted out.
     */
    *c = (uint32_t)(s[0] & masks[len]) << 18;
    *c |= (uint32_t)(s[1] & 0x3f) << 12;
    *c |= (uint32_t)(s[2] & 0x3f) << 6;
    *c |= (uint32_t)(s[3] & 0x3f) << 0;
    *c >>= shiftc[len];

    /* Accumulate the various error conditions. */
    *e = (*c < mins[len]) << 6;      // non-canonical encoding
    *e |= ((*c >> 11) == 0x1b) << 7; // surrogate half?
    *e |= (*c > 0x10FFFF) << 8;      // out of range?
    *e |= (s[1] & 0xc0) >> 2;
    *e |= (s[2] & 0xc0) >> 4;
    *e |= (s[3]) >> 6;
    *e ^= 0x2a; // top two bits of each tail byte correct?
    *e >>= shifte[len];

    return next;
  }

  static ZenEvent TranslateTextInputEvent(const SDL_Event &e) {
    ZenEvent event{};
    event.header.category = EventCategory::Input | EventCategory::Text;
    event.header.type     = EventType::TextInput;

    uint32_t codepoint;
    int error;

    utf8_decode((void *)e.text.text, &codepoint, &error);
    event.textInput.codepoint = (error ? U'\uFFFD' : static_cast<char32_t>(codepoint));
    return event;
  }

  static ZenEvent TranslateApplicationEvent(const SDL_Event &e) {
    ZenEvent event{};
    event.header.category = EventCategory::Application;
    event.header.type     = EventType::Quit;

    return event;
  }

  ZenEvent TranslateEvent(const SDL_Event &e) {
    switch (e.type) {
      case SDL_EVENT_QUIT:
        return TranslateApplicationEvent(e);
      case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
      case SDL_EVENT_WINDOW_RESIZED:
      case SDL_EVENT_WINDOW_FOCUS_GAINED:
      case SDL_EVENT_WINDOW_FOCUS_LOST:
      case SDL_EVENT_WINDOW_MOVED:
        return TranslateWindowEvent(e);
      case SDL_EVENT_KEY_DOWN:
      case SDL_EVENT_KEY_UP:
        return TranslateKeyEvent(e);
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
      case SDL_EVENT_MOUSE_BUTTON_UP:
      case SDL_EVENT_MOUSE_MOTION:
      case SDL_EVENT_MOUSE_WHEEL:
        return TranslateMouseEvent(e);
      case SDL_EVENT_TEXT_INPUT:
        return TranslateTextInputEvent(e);

      default: {
        ZenEvent event{};
        event.header.type     = EventType::None;
        event.header.category = EventCategory::None;
        return event;
      }
    }
  }
} // namespace Zen
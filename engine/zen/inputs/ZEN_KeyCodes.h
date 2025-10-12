#pragma once

#include <zen/zen_pch.h>

namespace Zen {
  enum class KeyModifier : uint16_t {
    None  = 0,
    Shift = 1 << 0,
    Ctrl  = 1 << 1,
    Alt   = 1 << 2,
    Super = 1 << 3,
    Caps  = 1 << 4,
    Num   = 1 << 5
  };

  constexpr KeyModifier operator|(KeyModifier a, KeyModifier b) {
    return static_cast<KeyModifier>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
  }

  constexpr KeyModifier operator&(KeyModifier a, KeyModifier b) {
    return static_cast<KeyModifier>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
  }

  constexpr KeyModifier &operator|=(KeyModifier &a, KeyModifier b) {
    a = a | b;
    return a;
  }

  constexpr KeyModifier mapSDLMods(SDL_Keymod currentMod) {
    KeyModifier mods = KeyModifier::None;

    if (currentMod & SDL_KMOD_SHIFT) {
      mods |= KeyModifier::Shift;
    }
    if (currentMod & SDL_KMOD_CTRL) {
      mods |= KeyModifier::Ctrl;
    }
    if (currentMod & SDL_KMOD_ALT) {
      mods |= KeyModifier::Alt;
    }
    if (currentMod & SDL_KMOD_GUI) {
      mods |= KeyModifier::Super;
    }
    if (currentMod & SDL_KMOD_CAPS) {
      mods |= KeyModifier::Caps;
    }
    if (currentMod & SDL_KMOD_NUM) {
      mods |= KeyModifier::Num;
    }

    return mods;
  }

  using ScanCode = std::uint16_t;

  namespace Key {

    static constexpr ScanCode Unknown = 0;

    static constexpr ScanCode A = 4;
    static constexpr ScanCode B = 5;
    static constexpr ScanCode C = 6;
    static constexpr ScanCode D = 7;
    static constexpr ScanCode E = 8;
    static constexpr ScanCode F = 9;
    static constexpr ScanCode G = 10;
    static constexpr ScanCode H = 11;
    static constexpr ScanCode I = 12;
    static constexpr ScanCode J = 13;
    static constexpr ScanCode K = 14;
    static constexpr ScanCode L = 15;
    static constexpr ScanCode M = 16;
    static constexpr ScanCode N = 17;
    static constexpr ScanCode O = 18;
    static constexpr ScanCode P = 19;
    static constexpr ScanCode Q = 20;
    static constexpr ScanCode R = 21;
    static constexpr ScanCode S = 22;
    static constexpr ScanCode T = 23;
    static constexpr ScanCode U = 24;
    static constexpr ScanCode V = 25;
    static constexpr ScanCode W = 26;
    static constexpr ScanCode X = 27;
    static constexpr ScanCode Y = 28;
    static constexpr ScanCode Z = 29;

    // Number row (top digits)
    static constexpr ScanCode D1 = 30;
    static constexpr ScanCode D2 = 31;
    static constexpr ScanCode D3 = 32;
    static constexpr ScanCode D4 = 33;
    static constexpr ScanCode D5 = 34;
    static constexpr ScanCode D6 = 35;
    static constexpr ScanCode D7 = 36;
    static constexpr ScanCode D8 = 37;
    static constexpr ScanCode D9 = 38;
    static constexpr ScanCode D0 = 39;

    // Controls / Punctuation
    static constexpr ScanCode Enter        = 40;
    static constexpr ScanCode Escape       = 41;
    static constexpr ScanCode Backspace    = 42;
    static constexpr ScanCode Tab          = 43;
    static constexpr ScanCode Space        = 44;
    static constexpr ScanCode Minus        = 45;
    static constexpr ScanCode Equals       = 46;
    static constexpr ScanCode LeftBracket  = 47;
    static constexpr ScanCode RightBracket = 48;
    static constexpr ScanCode Backslash    = 49;
    static constexpr ScanCode NonUSHash    = 50;
    static constexpr ScanCode Semicolon    = 51;
    static constexpr ScanCode Apostrophe   = 52;
    static constexpr ScanCode Grave        = 53;
    static constexpr ScanCode Comma        = 54;
    static constexpr ScanCode Period       = 55;
    static constexpr ScanCode Slash        = 56;
    static constexpr ScanCode CapsLock     = 57;

    // Function keys
    static constexpr ScanCode F1          = 58;
    static constexpr ScanCode F2          = 59;
    static constexpr ScanCode F3          = 60;
    static constexpr ScanCode F4          = 61;
    static constexpr ScanCode F5          = 62;
    static constexpr ScanCode F6          = 63;
    static constexpr ScanCode F7          = 64;
    static constexpr ScanCode F8          = 65;
    static constexpr ScanCode F9          = 66;
    static constexpr ScanCode F10         = 67;
    static constexpr ScanCode F11         = 68;
    static constexpr ScanCode F12         = 69;
    static constexpr ScanCode PrintScreen = 70;
    static constexpr ScanCode ScrollLock  = 71;
    static constexpr ScanCode Pause       = 72;

    // Navigation / Editing
    static constexpr ScanCode Insert   = 73;
    static constexpr ScanCode Home     = 74;
    static constexpr ScanCode PageUp   = 75;
    static constexpr ScanCode Delete   = 76;
    static constexpr ScanCode End      = 77;
    static constexpr ScanCode PageDown = 78;
    static constexpr ScanCode Right    = 79;
    static constexpr ScanCode Left     = 80;
    static constexpr ScanCode Down     = 81;
    static constexpr ScanCode Up       = 82;

    // Numpad (Keypad)
    static constexpr ScanCode NumLockClear = 83;
    static constexpr ScanCode KpDivide     = 84;
    static constexpr ScanCode KpMultiply   = 85;
    static constexpr ScanCode KpMinus      = 86;
    static constexpr ScanCode KpPlus       = 87;
    static constexpr ScanCode KpEnter      = 88;
    static constexpr ScanCode Kp1          = 89;
    static constexpr ScanCode Kp2          = 90;
    static constexpr ScanCode Kp3          = 91;
    static constexpr ScanCode Kp4          = 92;
    static constexpr ScanCode Kp5          = 93;
    static constexpr ScanCode Kp6          = 94;
    static constexpr ScanCode Kp7          = 95;
    static constexpr ScanCode Kp8          = 96;
    static constexpr ScanCode Kp9          = 97;
    static constexpr ScanCode Kp0          = 98;
    static constexpr ScanCode KpPeriod     = 99;

    // Misc / International
    static constexpr ScanCode NonUSBackslash = 100;
    static constexpr ScanCode Application    = 101;
    static constexpr ScanCode Power          = 102;
    static constexpr ScanCode KpEquals       = 103;
    static constexpr ScanCode F13            = 104;
    static constexpr ScanCode F14            = 105;
    static constexpr ScanCode F15            = 106;
    static constexpr ScanCode F16            = 107;
    static constexpr ScanCode F17            = 108;
    static constexpr ScanCode F18            = 109;
    static constexpr ScanCode F19            = 110;
    static constexpr ScanCode F20            = 111;
    static constexpr ScanCode F21            = 112;
    static constexpr ScanCode F22            = 113;
    static constexpr ScanCode F23            = 114;
    static constexpr ScanCode F24            = 115;
    static constexpr ScanCode Execute        = 116;
    static constexpr ScanCode Help           = 117;
    static constexpr ScanCode Menu           = 118;
    static constexpr ScanCode Select         = 119;
    static constexpr ScanCode Stop           = 120;
    static constexpr ScanCode Again          = 121;
    static constexpr ScanCode Undo           = 122;
    static constexpr ScanCode Cut            = 123;
    static constexpr ScanCode Copy           = 124;
    static constexpr ScanCode Paste          = 125;
    static constexpr ScanCode Find           = 126;
    static constexpr ScanCode Mute           = 127;
    static constexpr ScanCode VolumeUp       = 128;
    static constexpr ScanCode VolumeDown     = 129;

    static constexpr ScanCode KpComma       = 133;
    static constexpr ScanCode KpEqualsAS400 = 134;

    static constexpr ScanCode International1 = 135;
    static constexpr ScanCode International2 = 136;
    static constexpr ScanCode International3 = 137; // Yen
    static constexpr ScanCode International4 = 138;
    static constexpr ScanCode International5 = 139;
    static constexpr ScanCode International6 = 140;
    static constexpr ScanCode International7 = 141;
    static constexpr ScanCode International8 = 142;
    static constexpr ScanCode International9 = 143;

    static constexpr ScanCode Lang1 = 144; // Hangul/English
    static constexpr ScanCode Lang2 = 145; // Hanja
    static constexpr ScanCode Lang3 = 146; // Katakana
    static constexpr ScanCode Lang4 = 147; // Hiragana
    static constexpr ScanCode Lang5 = 148; // Zenkaku/Hankaku
    static constexpr ScanCode Lang6 = 149; // reserved
    static constexpr ScanCode Lang7 = 150; // reserved
    static constexpr ScanCode Lang8 = 151; // reserved
    static constexpr ScanCode Lang9 = 152; // reserved

    static constexpr ScanCode AltErase   = 153;
    static constexpr ScanCode SysReq     = 154;
    static constexpr ScanCode Cancel     = 155;
    static constexpr ScanCode Clear      = 156;
    static constexpr ScanCode Prior      = 157;
    static constexpr ScanCode Return2    = 158;
    static constexpr ScanCode Separator  = 159;
    static constexpr ScanCode Out        = 160;
    static constexpr ScanCode Oper       = 161;
    static constexpr ScanCode ClearAgain = 162;
    static constexpr ScanCode CrSel      = 163;
    static constexpr ScanCode ExSel      = 164;

    // Extended Keypad
    static constexpr ScanCode Kp00               = 176;
    static constexpr ScanCode Kp000              = 177;
    static constexpr ScanCode ThousandsSeparator = 178;
    static constexpr ScanCode DecimalSeparator   = 179;
    static constexpr ScanCode CurrencyUnit       = 180;
    static constexpr ScanCode CurrencySubUnit    = 181;
    static constexpr ScanCode KpLeftParen        = 182;
    static constexpr ScanCode KpRightParen       = 183;
    static constexpr ScanCode KpLeftBrace        = 184;
    static constexpr ScanCode KpRightBrace       = 185;
    static constexpr ScanCode KpTab              = 186;
    static constexpr ScanCode KpBackspace        = 187;
    static constexpr ScanCode KpA                = 188;
    static constexpr ScanCode KpB                = 189;
    static constexpr ScanCode KpC                = 190;
    static constexpr ScanCode KpD                = 191;
    static constexpr ScanCode KpE                = 192;
    static constexpr ScanCode KpF                = 193;
    static constexpr ScanCode KpXor              = 194;
    static constexpr ScanCode KpPower            = 195;
    static constexpr ScanCode KpPercent          = 196;
    static constexpr ScanCode KpLess             = 197;
    static constexpr ScanCode KpGreater          = 198;
    static constexpr ScanCode KpAmpersand        = 199;
    static constexpr ScanCode KpDblAmpersand     = 200;
    static constexpr ScanCode KpVerticalBar      = 201;
    static constexpr ScanCode KpDblVerticalBar   = 202;
    static constexpr ScanCode KpColon            = 203;
    static constexpr ScanCode KpHash             = 204;
    static constexpr ScanCode KpSpace            = 205;
    static constexpr ScanCode KpAt               = 206;
    static constexpr ScanCode KpExclam           = 207;
    static constexpr ScanCode KpMemStore         = 208;
    static constexpr ScanCode KpMemRecall        = 209;
    static constexpr ScanCode KpMemClear         = 210;
    static constexpr ScanCode KpMemAdd           = 211;
    static constexpr ScanCode KpMemSubtract      = 212;
    static constexpr ScanCode KpMemMultiply      = 213;
    static constexpr ScanCode KpMemDivide        = 214;
    static constexpr ScanCode KpPlusMinus        = 215;
    static constexpr ScanCode KpClear            = 216;
    static constexpr ScanCode KpClearEntry       = 217;
    static constexpr ScanCode KpBinary           = 218;
    static constexpr ScanCode KpOctal            = 219;
    static constexpr ScanCode KpDecimal          = 220;
    static constexpr ScanCode KpHexadecimal      = 221;

    // Modifiers
    static constexpr ScanCode LCtrl  = 224;
    static constexpr ScanCode LShift = 225; // you already had this
    static constexpr ScanCode LAlt   = 226;
    static constexpr ScanCode LGUI   = 227;
    static constexpr ScanCode RCtrl  = 228;
    static constexpr ScanCode RShift = 229; // you already had this
    static constexpr ScanCode RAlt   = 230;
    static constexpr ScanCode RGUI   = 231;

    // Mode (special modifier)
    static constexpr ScanCode Mode = 257;

    // Consumer (USB page 0x0C)
    static constexpr ScanCode Sleep              = 258;
    static constexpr ScanCode Wake               = 259;
    static constexpr ScanCode ChannelIncrement   = 260;
    static constexpr ScanCode ChannelDecrement   = 261;
    static constexpr ScanCode MediaPlay          = 262;
    static constexpr ScanCode MediaPause         = 263;
    static constexpr ScanCode MediaRecord        = 264;
    static constexpr ScanCode MediaFastForward   = 265;
    static constexpr ScanCode MediaRewind        = 266;
    static constexpr ScanCode MediaNextTrack     = 267;
    static constexpr ScanCode MediaPreviousTrack = 268;
    static constexpr ScanCode MediaStop          = 269;
    static constexpr ScanCode MediaEject         = 270;
    static constexpr ScanCode MediaPlayPause     = 271;
    static constexpr ScanCode MediaSelect        = 272;
    static constexpr ScanCode AC_New             = 273;
    static constexpr ScanCode AC_Open            = 274;
    static constexpr ScanCode AC_Close           = 275;
    static constexpr ScanCode AC_Exit            = 276;
    static constexpr ScanCode AC_Save            = 277;
    static constexpr ScanCode AC_Print           = 278;
    static constexpr ScanCode AC_Properties      = 279;
    static constexpr ScanCode AC_Search          = 280;
    static constexpr ScanCode AC_Home            = 281;
    static constexpr ScanCode AC_Back            = 282;
    static constexpr ScanCode AC_Forward         = 283;
    static constexpr ScanCode AC_Stop            = 284;
    static constexpr ScanCode AC_Refresh         = 285;
    static constexpr ScanCode AC_Bookmarks       = 286;

    // Mobile
    static constexpr ScanCode SoftLeft  = 287;
    static constexpr ScanCode SoftRight = 288;
    static constexpr ScanCode Call      = 289;
    static constexpr ScanCode EndCall   = 290;

    // Reserved ranges / counters
    static constexpr ScanCode Reserved = 400; // reserved for dynamic keycodes (400..500)
    static constexpr ScanCode Count    = 512; // not a key; size sentinel

    // Useful aliases
    static constexpr ScanCode Return    = Enter; // SDL name
    static constexpr ScanCode LeftCtrl  = LCtrl;
    static constexpr ScanCode LeftAlt   = LAlt;
    static constexpr ScanCode LeftGUI   = LGUI;
    static constexpr ScanCode RightCtrl = RCtrl;
    static constexpr ScanCode RightAlt  = RAlt;
    static constexpr ScanCode RightGUI  = RGUI;

  } // namespace Key

} // namespace Zen

///
/// A "keyboard" event
/// 

#pragma once

#include "Event.h"

namespace df {

const std::string KEYBOARD_EVENT = "df::keyboard";

/// Types of keyboard actions Dragonfly recognizes.
enum EventKeyboardAction {
  UNDEFINED_KEYBOARD_ACTION = -1, ///< Undefined
  KEY_PRESSED,			  ///< Was down
  KEY_RELEASED,			  ///< Was released
  KEY_DOWN,			  ///< Is down
};

/// Keyboard namespace.
namespace Keyboard {
/// Keys Dragonfly recognizes.
enum Key {
  UNDEFINED_KEY = -1, 
  SPACE, RETURN, ESCAPE, TAB, Left, Right, Up, Down, 
  PAUSE, DASH, PLUS, TILDE, PERIOD, COMMA, SLASH, 
  EQUAL, BACKSLASH, MULTIPLY, QUOTE, SEMICOLON,
  LEFTCONTROL, RIGHTCONTROL,
  LEFTSHIFT, RIGHTSHIFT, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, 
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0, BACKSPACE,
};
} // end of namespace Keyboard

class EventKeyboard : public Event {

 private:
  Keyboard::Key key_val;	          ///< Key value.
  EventKeyboardAction keyboard_action;    ///< Key action.

 public:
  EventKeyboard();

  /// Set key in event.
  void setKey(Keyboard::Key new_key);

  /// Get key from event.
  Keyboard::Key getKey() const;

  /// Set keyboard event action.
  void setKeyboardAction(EventKeyboardAction new_action);

  /// Get keyboard event action.
  EventKeyboardAction getKeyboardAction() const;
};

} // end of namespace df


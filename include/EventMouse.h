///
/// A "mouse" event
///

#pragma once

#include "Event.h"
#include "Vector.h"

namespace df {

const std::string MOUSE_EVENT = "df::mouse";

/// Set of mouse actions recognized by Dragonfly.
enum EventMouseAction {
  UNDEFINED_MOUSE_ACTION = -1,
  CLICKED,
  PRESSED,
  MOVED,
};

/// Set of mouse buttons recognized by Dragonfly.
namespace Mouse {
enum EventMouseButton {
  UNDEFINED_MOUSE_BUTTON = -1,
  LEFT,
  RIGHT,
  MIDDLE,
};
} // end of namespace Mouse
  
class EventMouse : public Event {

 private:
  EventMouseAction mouse_action;         ///< Mouse action.
  Mouse::EventMouseButton mouse_button;  ///< Mouse button.
  Vector mouse_xy;		         ///< Mouse (x,y) coordinates.

 public:
  EventMouse();

  /// Set mouse event's action.
  void setMouseAction(EventMouseAction new_mouse_action);

  /// Get mouse event's action.
  EventMouseAction getMouseAction() const;

  /// Set mouse event's button.
  void setMouseButton(Mouse::EventMouseButton new_mouse_button);

  /// Get mouse event's button.
  Mouse::EventMouseButton getMouseButton() const;

  /// Set mouse event's position.
  void setMousePosition(Vector new_mouse_xy);

  /// Get mouse event's position.
  Vector getMousePosition() const;
};

} // end of namespace df

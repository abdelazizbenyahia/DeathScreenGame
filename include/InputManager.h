///
/// The SFML input manager
///
#pragma once
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Manager.h"
#include "SFML/Graphics.hpp"
namespace df {
	
///change sfml key event to df key board event
df::Keyboard::Key sfkeyboardToDfKeyboard(sf::Keyboard::Key k);
///change sfml key event to df key board event
sf::Keyboard::Key dfkeyboardToSfKeyboard(df::Keyboard::Key k);
///change df mouse button to sf mouse button
sf::Mouse::Button dfmouseToSfMouse(df::Mouse::EventMouseButton k);
///change sf mouse button to df mouse button
df::Mouse::EventMouseButton sfmouseToDfMouse(sf::Mouse::Button k);
const std::string INPUT_MANAGER = "df::input_manager";
class InputManager : public Manager {

 private:
  InputManager();                      ///< Private since a singleton.
  InputManager (InputManager const&);  ///< Don't allow copy.
  void operator=(InputManager const&); ///< Don't allow assignment.

 public:
  /// Get the one and only instance of the InputManager.
  static InputManager &getInstance();

  /// Input manager only accepts keyboard and mouse events.
  /// Return false if not one of them.
  bool isValid(std::string event_type) const;

  /// Get window ready to capture input.  
  /// Return 0 if ok, else return -1;
  int startUp();

  /// Revert back to normal window mode.
  void shutDown();

  /// Get input from the keyboard and mouse.
  /// Pass event along to all interested Objects.
  void getInput();
};

} // end of namespace df
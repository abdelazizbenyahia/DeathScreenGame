///
/// The game manager
///

#pragma once

#include "Manager.h"


namespace df {
const std::string GAME_MANAGER = "df::game_manager";
/// Dragonfly cofiguration file.
const std::string CONFIG_FILENAME = "df-config.txt";

/// Default frame time (game loop time) in milliseconds (33 ms == 30 f/s).
const int FRAME_TIME_DEFAULT = 33;

class GameManager : public Manager {

 private:
  GameManager();                      ///< Private since a singleton.
  GameManager (GameManager const&);   ///< Don't allow copy.
  void operator=(GameManager const&); ///< Don't allow assignment.
  bool game_over;           ///< True -> game loop should stop.
  int frame_time;           ///< Target time per game loop, in millisec.
  int step_count;			///<Step count
  
 public:
  /// Get the singleton instance of the GameManager.
  static GameManager &getInstance();

  /// Startup all GameManager services.
  int startUp();

  /// Game manager only accepts step events.
  /// Return false if other event.
  bool isValid(std::string event_name) const;

  /// Shut down GameManager services.
  void shutDown();

  /// Run game loop.
  void run();

  /// Set game over status to indicated value.
  /// If true (default), will stop game loop.
  void setGameOver(bool game_over=true);

  /// Get game over status.
  bool getGameOver() const;

  /// Return frame time.  
  /// Frame time is target time for each game loop, in milliseconds.
  int getFrameTime() const;
  
  /// Return game loop step count.
  int getStepCount() const;
};

} // end of namespace df

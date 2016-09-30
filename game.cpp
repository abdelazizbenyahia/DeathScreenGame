//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "Pause.h"
#include "ResourceManager.h"
 
// Game includes.

// Function prototypes.
void loadResources(void);
void populateWorld(void);
 
int main(int argc, char *argv[]) {
  df::LogManager &log_manager = df::LogManager::getInstance();

  // Start up game manager.
  df::GameManager &game_manager = df::GameManager::getInstance();
  if (game_manager.startUp())  {
    log_manager.writeLog("Error starting game manager!");
    game_manager.shutDown();
    return 0;
  }

  // Set flush of logfile during development (when done, make false).
  log_manager.setFlush(true);

  // Load game resources.
  loadResources();

  // Populate game world with some objects.
  populateWorld();
 
  // Run game (this blocks until game loop is over).
  game_manager.run();
 
  // Shut everything down.
  game_manager.shutDown();
}
 
// Load resources (sprites, sound effects, music).
void loadResources(void) {
  df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
}
 
// Populate world with some objects.
void populateWorld(void) {
}

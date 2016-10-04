//
// game.cpp
//

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "Pause.h"
#include "ResourceManager.h"
#include "ViewObject.h"
// Game includes.
#include "ErrorsObjectList.h"
// Function prototypes.
void loadResources(void);
void populateWorld(void);

int main(int argc, char* argv[])
{
    df::LogManager& log_manager = df::LogManager::getInstance();

    // Start up game manager.
    df::GameManager& game_manager = df::GameManager::getInstance();
    if(game_manager.startUp()) {
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
void loadResources(void)
{
    df::ResourceManager& resource_manager = df::ResourceManager::getInstance();
	resource_manager.loadSprite("sprites/explosion-spr.txt", "explosion");
	resource_manager.loadSound("sounds/errors-sound.wav", "errors");
	resource_manager.loadSound("sounds/fire.wav", "fire");
	//normal theme
	resource_manager.loadMusic("sounds/spectre.wav", "spectre");
	//extreme theme
	//resource_manager.loadMusic("sounds/Miiro.mp3", "miiro");
}

// Populate world with some objects.
void populateWorld(void)
{
	new ErrorsObjectList;
	df::ViewObject * v_o = new df::ViewObject();
	v_o->setViewString("Points");
	v_o->setValue(0);
}

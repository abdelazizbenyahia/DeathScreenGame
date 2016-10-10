//
// game.cpp
//

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "Pause.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "ViewObject.h"
#include "GraphicsManager.h"
// Game includes.
#include "GameStart.h"
#include "ErrorsObjectList.h"
#include "Hero.h"
// Function prototypes.
void loadResources(void);
void populateWorld(void);

int main(int argc, char* argv[])
{
    df::LogManager& log_manager = df::LogManager::getInstance();
	df::GraphicsManager& graphics = df::GraphicsManager::getInstance();
	df::WorldManager& world = df::WorldManager::getInstance();
	
    // Start up game manager.
    df::GameManager& game_manager = df::GameManager::getInstance();
    if(game_manager.startUp()) {
	log_manager.writeLog("Error starting game manager!");

	game_manager.shutDown();
	return 0;
    }
	sf::Color blue = sf::Color(7, 61, 147);
	graphics.setBackgroundColor(blue);
	graphics.setBackgroundTextColor(blue);
    // Set flush of logfile during development (when done, make false).
    log_manager.setFlush(false);

    // Load game resources.
    loadResources();

    // Populate game world with some objects.
    populateWorld();
new df::Pause(df::Keyboard::F10);
    // Run game (this blocks until game loop is over).
    game_manager.run();

    // Shut everything down.
    game_manager.shutDown();
}

// Load resources (sprites, sound effects, music).
void loadResources(void)
{
    df::ResourceManager& resource_manager = df::ResourceManager::getInstance();
    resource_manager.loadSprite("../sprites/explosion-spr.txt", "explosion");
    resource_manager.loadSprite("../sprites/ship-spr.txt", "ship");
    resource_manager.loadSound("../sounds/errors-sound.wav", "errors");
    resource_manager.loadSound("../sounds/fire.wav", "fire");
    resource_manager.loadSound("../sounds/blast.wav", "blast");
    resource_manager.loadSound("../sounds/game-over.wav", "game over");
	resource_manager.loadSprite("../sprites/gamestart-spr.txt", "gamestart");
    resource_manager.loadSprite("../sprites/gameover-spr.txt", "gameover");
    // normal theme
    resource_manager.loadMusic("../sounds/spectre.wav", "spectre");
	resource_manager.loadMusic("../sounds/start-music.wav", "start music");
    // extreme theme
    // resource_manager.loadMusic("sounds/Miiro.mp3", "miiro");
}

// Populate world with some objects.
void populateWorld(void)
{
	new GameStart();
    new Hero;
    new ErrorsObjectList;
    df::ViewObject* v_o = new df::ViewObject();
    v_o->setViewString("Points");
    v_o->setValue(0);
}

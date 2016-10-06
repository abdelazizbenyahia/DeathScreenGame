#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameOver.h"
#include "GameManager.h"

void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0) {
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		world_manager.markForDelete(this);
	}
}

void GameOver::draw() {
	df::Object::draw();
}

GameOver::GameOver() {

  setType("GameOver");

  // Link to "message" sprite.
  df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
  df::Sprite *p_temp_sprite = resource_manager.getSprite("gameover");
  if (!p_temp_sprite) {
    df::LogManager &log_manager = df::LogManager::getInstance();
    log_manager.writeLog("GameOver::GameOver(): Warning! Sprite 'gameover' not found");
  } else {
    setSprite(p_temp_sprite);
    setSpriteSlowdown(15);		  
    setTransparency('#');    // Transparent character.
    time_to_live = p_temp_sprite->getFrameCount() * 15; // setting time to live 15
  }
  df::Sound *p_sound = df::ResourceManager::getInstance().getSound("game over");
  p_sound->play();
  setLocation(df::CENTER_CENTER);
  registerInterest(df::STEP_EVENT);

}
GameOver::~GameOver() {
  df::GameManager& game = df::GameManager::getInstance();
  game.setGameOver();
  
  
}

int GameOver::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }


  return 0;
}



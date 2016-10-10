#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameStart.h"
#include "Hero.h"
#include "Music.h"
#include "Color.h"
#include "EventKeyboard.h"

GameStart::GameStart() {
  setType("GameStart");
  df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
  df::Sprite *p_temp_sprite = resource_manager.getSprite("gamestart");
  if (!p_temp_sprite) {
    df::LogManager &log_manager = df::LogManager::getInstance();
    log_manager.writeLog("GameStart::GameStart(): Warning! Sprite 'gamestart' not found");
  } else {
    setSprite(p_temp_sprite);
    setSpriteSlowdown(15);		  
  }
  
  // Put in center of screen.
  setLocation(df::CENTER_CENTER);

  // Register for "keyboard" event.
  registerInterest(df::KEYBOARD_EVENT);

  p_music = df::ResourceManager::getInstance().getMusic("start music");
  playMusic();
}
int GameStart::eventHandler(const df::Event *p_e) {
  df::GameManager &game_manager = df::GameManager::getInstance();

  if (p_e->getType() == df::KEYBOARD_EVENT) {
    df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;
    switch (p_keyboard_event->getKey()) {
    case df::Keyboard::P: 			// play
      start();
      break;
    case df::Keyboard::Q:			// quit
      game_manager.setGameOver();
      break;
    default:
      break;
    }
    return 1;
  }
  return 0;
}
void GameStart::playMusic() {
	p_music->play();
}
void GameStart::playOnReturn() {
	p_music->pause();
	p_music = df::ResourceManager::getInstance().getMusic("start music");
	p_music->play();
}
void GameStart::start() {
  setIsActive(false);
  p_music->pause();
  p_music = df::ResourceManager::getInstance().getMusic("ingame");
  playMusic();
}

void GameStart::draw() {
  df::Object::draw();
}

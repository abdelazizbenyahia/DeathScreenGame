#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameOver.h"
#include "GameManager.h"
#include "EventGameOver.h"
#include "EventKeyboard.h"

void GameOver::step()
{
}

void GameOver::draw()
{
    df::Object::draw();
}

GameOver::GameOver()
{

    setType("GameOver");

    // Link to "message" sprite.
    df::ResourceManager& resource_manager = df::ResourceManager::getInstance();
    df::Sprite* p_temp_sprite = resource_manager.getSprite("gameover");
    if(!p_temp_sprite) {
	df::LogManager& log_manager = df::LogManager::getInstance();
	log_manager.writeLog("GameOver::GameOver(): Warning! Sprite 'gameover' not found");
    } else {
	setSprite(p_temp_sprite);
	setSpriteSlowdown(15);
	setTransparency('#');                               // Transparent character.
	time_to_live = p_temp_sprite->getFrameCount() * 15; // setting time to live 15
    }
    df::Sound* p_sound = df::ResourceManager::getInstance().getSound("game over");
    p_sound->play();
    setLocation(df::CENTER_CENTER);
    registerInterest(df::STEP_EVENT);
    df::WorldManager& world = df::WorldManager::getInstance();
    EventGameOver ego;
    world.onEvent(&ego);
    registerInterest(df::KEYBOARD_EVENT);
}
GameOver::~GameOver()
{
}

int GameOver::eventHandler(const df::Event* p_e)
{

    if(p_e->getType() == df::STEP_EVENT) {
	step();
	return 1;
    }

    if(p_e->getType() == df::KEYBOARD_EVENT) {
	const df::EventKeyboard* e = static_cast<const df::EventKeyboard*>(p_e);
	if(e->getKey() == df::Keyboard::Key::R && e->getKeyboardAction() == df::EventKeyboardAction::KEY_RELEASED) {
		return 1;
	}
    }
    return 0;
}

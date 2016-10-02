//
// Hero.cpp
//

// Engine includes.
#include "EventMouse.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "utility.h"
#include "InputManager.h"
// Game includes.
#include "Hero.h"
#include "Explosion.h"
// Define registerInterest in case engine does not.
static void registerInterest(std::string s){};

Hero::Hero()
{

    // Link to "ship" sprite.
    df::ResourceManager& resource_manager = df::ResourceManager::getInstance();
    df::LogManager& log_manager = df::LogManager::getInstance();
    df::Sprite* p_temp_sprite;
    p_temp_sprite = resource_manager.getSprite("ship");
    if(!p_temp_sprite) {
	log_manager.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "ship");
    } else {
	setSprite(p_temp_sprite);
	setSpriteSlowdown(3); // 1/3 speed animation.
	                      //    setTransparency();	   // Transparent sprite.
    }

    // Player controls hero, so register for input events.
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::MOUSE_EVENT);

    // Need to update rate control each step.
    registerInterest(df::STEP_EVENT);

    // Set object type.
    setType("Hero");

    // Set starting location.
    df::WorldManager& world_manager = df::WorldManager::getInstance();
    df::Vector p(7, world_manager.getBoundary().getVertical() / 2);
    setPos(p);
    if(world_manager.setViewFollowing(this) == -1) {
	log_manager.writeLog("cannot");
    }
    

    // Set attributes that control actions.
    move_slowdown = 2;
    move_countdown = move_slowdown;
    }

Hero::~Hero()
{

    
    // Make big explosion.
    for(int i = -8; i <= 8; i += 5) {
	for(int j = -5; j <= 5; j += 3) {
	    df::Vector temp_pos = this->getPos();
	    temp_pos.setX(this->getPos().getX() + i);
	    temp_pos.setY(this->getPos().getY() + j);
	    Explosion* p_explosion = new Explosion;
	    p_explosion->setPos(temp_pos);
	}
    }

  
}

// Handle event.
// Return 0 if ignored, else 1.
int Hero::eventHandler(const df::Event* p_e)
{

    if(p_e->getType() == df::KEYBOARD_EVENT) {
	const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*>(p_e);
	kbd(p_keyboard_event);
	return 1;
    }


    if(p_e->getType() == df::STEP_EVENT) {
	step();
	return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event)
{

}

// Move up or down.
void Hero::move(int dy)
{

    // See if time to move.
    if(move_countdown > 0)
	return;
    move_countdown = move_slowdown;

    // If stays on window, allow move.
    df::Vector new_pos(getPos().getX(), getPos().getY() + dy);
    df::WorldManager& world_manager = df::WorldManager::getInstance();
    if((new_pos.getY() > 3) && (new_pos.getY() < world_manager.getBoundary().getVertical() - 1)) {
	world_manager.moveObject(this, new_pos);
	}
}

void Hero::step()
{

    // Move countdown.
    move_countdown--;
    if(move_countdown < 0)
	move_countdown = 0;

}


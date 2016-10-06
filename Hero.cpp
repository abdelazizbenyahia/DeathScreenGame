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
	setSpriteSlowdown(2); // 1/3 speed animation.
	                      //    setTransparency();	   // Transparent sprite.
    }
    direction = true;
    // Player controls hero, so register for input events.

    // Set object type.
    setType("Hero");

    // Set starting location.
    df::WorldManager& world_manager = df::WorldManager::getInstance();
    df::Vector p(world_manager.getBoundary().getHorizontal() / 2, world_manager.getBoundary().getVertical() - 2);
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

    if(p_e->getType() == df::STEP_EVENT) {
	step();
	return 1;
    }
    if(p_e->getType() == df::COLLISION_EVENT) {
	const df::EventCollision* p_collision_event = dynamic_cast<df::EventCollision const*>(p_e);
	hit(p_collision_event);
	return 1;
    }
    return 0;
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event)
{
}

// Move up or down.
void Hero::move(int dx)
{

    // See if time to move.

    // If stays on window, allow move.
    df::Vector new_pos(getPos().getX() + dx, getPos().getY());
    df::WorldManager& world_manager = df::WorldManager::getInstance();
    if((new_pos.getX() > 3) && (new_pos.getX() < world_manager.getBoundary().getHorizontal() - 1)) {
	world_manager.moveObject(this, new_pos);
    }
}

void Hero::step()
{
    df::LogManager& log_manager = df::LogManager::getInstance();
    if(direction == true) {

	move(+1);
	if(this->getPos().getX() > 74)
	    direction = false;
	log_manager.writeLog("new position = ( %f %f )", this->getPos().getX(), this->getPos().getY());
    } else if(direction == false) {
	move(-1);
	if(this->getPos().getX() < 4.1f)
	    direction = true;
    }
}

void Hero::hit(const df::EventCollision* p_collision_event)
{

    if(((p_collision_event->getObject1()->getType()) == "ErrorsObject") ||
        ((p_collision_event->getObject2()->getType()) == "ErrorsObject")) {
	df::WorldManager& world_manager = df::WorldManager::getInstance();
	world_manager.markForDelete(p_collision_event->getObject1());
	world_manager.markForDelete(p_collision_event->getObject2());
    }
   
}
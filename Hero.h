//
// Hero.h
//
#pragma once
#include "EventKeyboard.h"
#include "Object.h"

#include "EventCollision.h"
class Hero : public df::Object
{

private:
    int move_countdown;
    int move_slowdown;
    bool direction;
    void kbd(const df::EventKeyboard* p_keyboard_event);
    void move(int dy);
    void step();
 void hit(const df::EventCollision *p_collision_event);
public:
    Hero();
    ~Hero();
    int eventHandler(const df::Event* p_e);
};

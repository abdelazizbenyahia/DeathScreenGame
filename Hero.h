//
// Hero.h
//

#include "EventKeyboard.h"
#include "Object.h"


class Hero : public df::Object
{

private:
    int move_countdown;
    int move_slowdown;

    void kbd(const df::EventKeyboard* p_keyboard_event);
    void move(int dy);
    void step();

public:
    Hero();
    ~Hero();
    int eventHandler(const df::Event* p_e);
};

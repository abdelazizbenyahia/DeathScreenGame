#include "Event.h"


const std::string GAMEOVER_EVENT = "game_over";

class EventGameOver : public df::Event {

 public:
  EventGameOver();
};
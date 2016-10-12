#include "EventGameOver.h"
#include "EventView.h"
#include "WorldManager.h"
EventGameOver::EventGameOver()
{
	df::Event::setType(GAMEOVER_EVENT);
	
}

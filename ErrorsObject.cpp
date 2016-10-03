#include "ErrorsObject.h"
#include "cstdlib"
#include "string"
#include "fstream"
//game engine
#include "WorldManager.h"
#include "GraphicsManager.h"

#include "EventOut.h"
#include "EventStep.h"
#include "LogManager.h"
#include "Color.h"

ErrorsObject::ErrorsObject(ErrorsObjectList *n_list, int max_num)
{
	max_number = max_num;
	list = n_list;
	loadContent();
	updateBox();
	color = df::WHITE;
	df::WorldManager& world = df::WorldManager::getInstance();
	int x = world.getBoundary().getHorizontal();
	int y = world.getBoundary().getVertical();
	df::Vector temp_pos;
	temp_pos.setX(rand() % (x - 4) + 4);
	temp_pos.setY(-3);
	setPos(temp_pos);
	setYVelocity(0.25);
	hardness = 1;
	
}

ErrorsObject::~ErrorsObject()
{
	if (list->getMaxObject() == this){
		list->setMaxObject(NULL);
		list->setMaxHeight(LOWEST_HEIGHT);
	}
}

int ErrorsObject::eventHandler(const df::Event* p_event)
{
	if (p_event->getType() == df::OUT_EVENT){
		df::WorldManager& world = df::WorldManager::getInstance();
		world.markForDelete(this);
		return 1;
	}
	if (p_event->getType() == df::STEP_EVENT){
		const df::EventStep * p_step_e = static_cast<const df::EventStep*>(p_event);
		int current_height = list->getMaxHeight();
		if (current_height < getPos().getY()){
			list->setMaxHeight(getPos().getY());
			list->setMaxObject(this);
		}
		return 1;
	}
	return 0;
}

void ErrorsObject::draw()
{
	df::GraphicsManager& graphics = df::GraphicsManager::getInstance();
	graphics.drawString(getPos(), content, df::CENTER_JUSTIFIED, color);
}

void ErrorsObject::loadContent()
{
	if (max_number == 0){
		content = "hello";
		updateBox();
		return;
	}
	int num = rand() % max_number;
	content = list->getContents(num);
	updateBox();
	return;
}

void ErrorsObject::updateBox()
{
	float size = content.size();
	df::Vector temp_corner(0 - size / 2.0, 0 - 1.0 / 2.0);
	df::Box b(temp_corner, size, 1);
	setBox(b);
}

int ErrorsObject::removeLetter(char c)
{
	if (c == 0) return 0;
	content.erase(std::remove(content.begin(), content.end(), c), content.end());
	if (content.size() == 0){
		df::WorldManager& world = df::WorldManager::getInstance();
		world.markForDelete(this);
		return 1;
	}
	updateBox();
	return 1;
}

df::Color ErrorsObject::getColor()
{
	return color;
}

void ErrorsObject::setColor(df::Color n_c)
{
	color = n_c;
}

int ErrorsObject::getHardness()
{
	return hardness;
}

void ErrorsObject::setHardness(int hard)
{
	hardness = hard;
}

void ErrorsObject::setMaxNumber(int max_num)
{
	max_number = max_num;
}

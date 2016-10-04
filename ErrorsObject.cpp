#include "ErrorsObject.h"
#include "cstdlib"
#include "string"
#include "fstream"
#include <cctype>
#include "Explosion.h"
// game engine
#include "WorldManager.h"
#include "GraphicsManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventStep.h"
#include "LogManager.h"
#include "Color.h"
#include "Sound.h"
#include "EventView.h"
#include "ObjectList.h"

ErrorsObject::ErrorsObject(ErrorsObjectList* n_list, int max_num)
{
    max_number = max_num;
    list = n_list;
    int r = rand() % 100;
    if(r < 100)
	hardness = 1;
    if(r < 30)
	hardness = 2;
    if(r < 10)
	hardness = 3;
    loadContent();
    color[0] = df::WHITE;
    color[1] = df::Color::MAGENTA;
    color[2] = df::RED;
	setYVelocity(0.1);
    moveToStart();
    
}

ErrorsObject::~ErrorsObject()
{
    if(list->getMaxObject() == this) {
	list->setMaxObject(NULL);
	list->setMaxHeight(LOWEST_HEIGHT);
    }
    df::ResourceManager& resource = df::ResourceManager::getInstance();
    df::Sound* s = resource.getSound("errors");
    if(s != NULL)
	s->play();
    Explosion* ex = new Explosion;
    ex->setPos(getPos());
	;
	
	
}

int ErrorsObject::eventHandler(const df::Event* p_event)
{
    if(p_event->getType() == df::OUT_EVENT) {
	df::WorldManager& world = df::WorldManager::getInstance();
	world.markForDelete(this);
	
	return 1;
    }
    if(p_event->getType() == df::STEP_EVENT) {
	const df::EventStep* p_step_e = static_cast<const df::EventStep*>(p_event);
	int current_height = list->getMaxHeight();
	if(current_height < getPos().getY()) {
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
	std::string bo(content[0].size() + 2, '-');
	graphics.drawString(df::Vector(getPos().getX(), getPos().getY() + 1), bo, df::CENTER_JUSTIFIED, color[hardness -1]);
	graphics.drawString(df::Vector(getPos().getX(), getPos().getY() - 1), bo, df::CENTER_JUSTIFIED, color[hardness -1]);
	graphics.drawString(getPos(), content[hardness - 1], df::CENTER_JUSTIFIED, color[hardness -1]);
    
}

void ErrorsObject::loadContent()
{
    if(max_number == 0) {
	for(int i = 0; i < hardness; i++) {
	    content[i] = "hello";
	}
	updateBox();
	return;
    }
    int num = rand() % max_number;
    for(int i = 0; i < hardness; i++) {
	content[i] = list->getContents(num);
    }

    updateBox();
    return;
}

void ErrorsObject::updateBox()
{
    float size = content[0].size();
    df::Vector temp_corner(0 - size / 2.0, 0 - 3.0 / 2.0);
    df::Box b(temp_corner, size, 3);
    setBox(b);
}

int ErrorsObject::removeLetter(char c)
{
    if(c == 0)
	return 0;
    content[hardness - 1].erase(
        std::remove(content[hardness - 1].begin(), content[hardness - 1].end(), c), content[hardness - 1].end());
    content[hardness - 1].erase(std::remove(content[hardness - 1].begin(), content[hardness - 1].end(), toupper(c)),
        content[hardness - 1].end());
    df::ResourceManager& resource = df::ResourceManager::getInstance();
    df::Sound* s = resource.getSound("fire");
    if(s != NULL)
	s->play();
    if(content[hardness - 1].size() == 0) {
	if(hardness - 1 == 0) {
	    df::WorldManager& world = df::WorldManager::getInstance();
	    world.markForDelete(this);
		df::EventView e_v("Points", 1, true);
		world.onEvent(&e_v);
	    return 1;
	}
	hardness--;
	Explosion* ex = new Explosion;
	ex->setAltitude(1);
    ex->setPos(getPos());
    }
    updateBox();
    return 1;
}

df::Color ErrorsObject::getColor(int c)
{
    if(c < 0 || c > 3) {
	c = 0;
    }
    return color[c];
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

void ErrorsObject::moveToStart()
{
    df::WorldManager& world_manager = df::WorldManager::getInstance();
    int x = world_manager.getBoundary().getHorizontal();
    df::Vector temp_pos;
    temp_pos.setX(rand() % (x - 4) + 4);
    temp_pos.setY(-3);
	if (temp_pos.getX() + getBox().getHorizontal() / 2 > x){
		temp_pos.setX(x - getBox().getHorizontal() - 1);
	}
    df::ObjectList collision_list = world_manager.isCollision(this, temp_pos);
    while(!collision_list.isEmpty()) {
	temp_pos.setY(temp_pos.getY() - 1);
	collision_list = world_manager.isCollision(this, temp_pos);
    }
	 
   setPos(temp_pos);
}

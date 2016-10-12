#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameOver.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "EventGameOver.h"
#include "EventKeyboard.h"
#include "GameStart.h"
#include "ErrorsObject.h"
#include "ViewObject.h"
#include "ErrorsObjectList.h"
#include <fstream>
#include "utility.h"
void GameOver::step()
{
}

void GameOver::draw()
{
	std::string hc = "Current highscore is " + df::intToString(highscore);
	df::GraphicsManager& graphics = df::GraphicsManager::getInstance();
	graphics.drawString(df::Vector(40, 3), hc, df::CENTER_JUSTIFIED, df::Color::WHITE);
    df::Object::draw();
}

GameOver::GameOver()
{

    setType("GameOver");
    // get highscore
    std::string line;
    highscore = 0;
    std::ifstream in("../data/score.txt");
    if(in.is_open()) {
	std::getline(in, line);
	highscore = strtol(line.c_str(), NULL, 10);
    }
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
    
	df::ObjectList ol = world.getAllObjects();
	df::ObjectListIterator it (&ol);
	while (!it.isDone()){
		df::Object* o = it.currentObject();
		if (o->getType() == df::VIEW_OBJECT){
			df::ViewObject * v_o = dynamic_cast<df::ViewObject*>(o);
			int score = v_o->getValue();
			if (score > highscore) {
				highscore = score;
				setHighScore(score);
			}
			world.markForDelete(o);
		}
		
		it.next();
	}
	
	registerInterest(df::KEYBOARD_EVENT);
    EventGameOver e;
    world.onEvent(&e);
}
GameOver::~GameOver()
{
    df::WorldManager& world_manager = df::WorldManager::getInstance();

    // Remove Saucers and ViewObjects, re-activate GameStart.
    df::ObjectList object_list = world_manager.getAllObjects(true);
    df::ObjectListIterator i(&object_list);
    for(i.first(); !i.isDone(); i.next()) {
	df::Object* p_o = i.currentObject();
	if(p_o->getType() == ERRORS_OBJECT || p_o->getType() == ELIST)
	    world_manager.markForDelete(p_o);
	if(p_o->getType() == df::VIEW_OBJECT)
	    dynamic_cast<df::ViewObject*>(p_o)->setValue(0);
	if(p_o->getType() == "GameStart") {
	    p_o->setIsActive(true);
	    dynamic_cast<GameStart*>(p_o)->playOnReturn(); // Resume start music.
	}
    }
    EventGameOver e;
    world_manager.onEvent(&e);
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
	    df::WorldManager& world = df::WorldManager::getInstance();
	    world.markForDelete(this);
	    return 1;
	}
    }
    return 0;
}

void GameOver::setHighScore(int score)
{
    std::string line;
    std::ifstream h_score("../data/score.txt");

    if(h_score.is_open()) {
	std::getline(h_score, line);
	int highscore = strtol(line.c_str(), NULL, 10);
	if(highscore < score) {
	    std::ofstream w("../data/score.txt", std::ios::trunc);
	    w << score;
	}
    } else {
	std::ofstream w("../data/score.txt", std::ios::trunc);
	w << score;
    }
}
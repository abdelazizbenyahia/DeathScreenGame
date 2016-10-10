#include "Music.h"
#include "ErrorsObjectList.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "LogManager.h"
#include <fstream>
#include "utility.h"
#include "ResourceManager.h"
#include "EventGameOver.h"
char dfKeyboardToChar(df::Keyboard::Key k);

ErrorsObjectList::ErrorsObjectList()
{
    highest_gap = 240;
    accelerate = 1;
    reduction = 0;
    max_height = LOWEST_HEIGHT;
    max_object = NULL;
    registerInterest(df::KEYBOARD_EVENT);
    setSolidness(df::SPECTRAL);
	loadContents();
	registerInterest(GAMEOVER_EVENT);
	df::ResourceManager& resource = df::ResourceManager::getInstance();
	df::Music * m = resource.getMusic("spectre");
	if (m!=NULL) m->play();
	
}

ErrorsObjectList::~ErrorsObjectList()
{
	df::ResourceManager& resource = df::ResourceManager::getInstance();
	df::Music * m = resource.getMusic("spectre");
	if (m != NULL)m->stop();

}

int ErrorsObjectList::eventHandler(const df::Event* p_event)
{
    if(p_event->getType() == df::STEP_EVENT) {
	const df::EventStep* p_step_e = static_cast<const df::EventStep*>(p_event);
	int step_num = p_step_e->getStepCount();
	step(step_num);
	return 1;
    }

    if(p_event->getType() == df::KEYBOARD_EVENT) {
	const df::EventKeyboard* p_key = static_cast<const df::EventKeyboard*>(p_event);
	if(p_key->getKeyboardAction() == df::KEY_RELEASED) {
	    if(max_object != NULL)
		max_object->removeLetter(dfKeyboardToChar(p_key->getKey()));
		return 1;
	}
    }
	
	if(p_event->getType() == GAMEOVER_EVENT) {
		start = !start;
		return 1;
    }

	
    return 0;
}

float ErrorsObjectList::getMaxHeight()
{
    return max_height;
}

void ErrorsObjectList::setMaxHeight(float n_height)
{
    max_height = n_height;
}

ErrorsObject* ErrorsObjectList::getMaxObject()
{
    return max_object;
}

void ErrorsObjectList::setMaxObject(ErrorsObject* n_object)
{
    max_object = n_object;
}

void ErrorsObjectList::step(int step_number)
{
	if (!start) return;
    int cap = highest_gap * accelerate - reduction;
    if(step_number % cap == 0) {
	new ErrorsObject(this, contents.size());
    }
	if (step_number % 600 == 0) {
		if (accelerate > 0.1)
		accelerate -= 0.1;
		
	}
}

void ErrorsObjectList::setAccelerate(float n_acce)
{
    accelerate = n_acce;
}

float ErrorsObjectList::getAccelerate()
{
    return accelerate;
}

void ErrorsObjectList::setReduction(float n_reduc)
{
    reduction = n_reduc;
}

float ErrorsObjectList::getReduction()
{
    return reduction;
}

void ErrorsObjectList::setHighestGap(int n_gap)
{
    highest_gap = n_gap;
}

int ErrorsObjectList::getHighestGap()
{
    return highest_gap;
}

void ErrorsObjectList::loadContents()
{
    ///“Nothing's perfect, the world's not perfect. But it's there for us,
    /// trying the best it can; that's what makes it so damn beautiful.” - totally not a quote in FullMetalAlchemist
    
    df::LogManager& log = df::LogManager::getInstance();
    std::string line;
    std::string filename = "../data/data.txt";
    std::ifstream myfile(filename);
    int line_num = 0;
    int curr;
    int hard;
    // Open file.
    if(myfile.is_open()) {
	int max_number = df::readLineInt(&myfile, &line_num, MAX_NUM_TOKEN);
	if(max_number == -1) {
	    log.writeLog("max numbers is wrong, wrong on line %d in file %s", line_num, filename.c_str());
	    return;
	}
	for(int i = 1; i <= max_number; i++) {
		std::getline(myfile, line);
	    line_num++;
	    if(line != "number " + df::intToString(i)) {
		log.writeLog("something missing, wrong on line %d in file %s", line_num, filename.c_str());
		return;
	    }

	    std::getline(myfile, line);
	    line_num++;
	    if(line == "") {
		log.writeLog("somethign is wrong, wrong on line %d in file %s", line_num, filename.c_str());
		return;
	    }
	    contents.push_back(line);
	}
    }
    return;
}

std::string ErrorsObjectList::getContents(int num)
{
	std::string re = contents[num];
	return re;
}

char dfKeyboardToChar(df::Keyboard::Key k)
{
    switch(k) {
    case df::Keyboard::Key::A:
	return 'a';
    case df::Keyboard::Key::B:
	return 'b';
    case df::Keyboard::Key::C:
	return 'c';
    case df::Keyboard::Key::D:
	return 'd';
    case df::Keyboard::Key::E:
	return 'e';
    case df::Keyboard::Key::F:
	return 'f';
    case df::Keyboard::Key::G:
	return 'g';
    case df::Keyboard::Key::H:
	return 'h';
    case df::Keyboard::Key::I:
	return 'i';
    case df::Keyboard::Key::J:
	return 'j';
    case df::Keyboard::Key::K:
	return 'k';
    case df::Keyboard::Key::L:
	return 'l';
    case df::Keyboard::Key::M:
	return 'm';
    case df::Keyboard::Key::N:
	return 'n';
    case df::Keyboard::Key::O:
	return 'o';
    case df::Keyboard::Key::P:
	return 'p';
    case df::Keyboard::Key::Q:
	return 'q';
    case df::Keyboard::Key::R:
	return 'r';
    case df::Keyboard::Key::S:
	return 's';
    case df::Keyboard::Key::T:
	return 't';
    case df::Keyboard::Key::U:
	return 'u';
    case df::Keyboard::Key::V:
	return 'v';
    case df::Keyboard::Key::W:
	return 'w';
    case df::Keyboard::Key::X:
	return 'x';
    case df::Keyboard::Key::Y:
	return 'y';
    case df::Keyboard::Key::Z:
	return 'z';
	case df::Keyboard::Key::SPACE:
	return ' ';
	case df::Keyboard::Key::QUOTE:
	return '\'';
    default:
	return 0;
    }
}

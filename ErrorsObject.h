
#pragma once
#include "Object.h"
#include "ErrorsObjectList.h"
class ErrorsObjectList;

const std::string HARDNESS_TOKEN = "hardness";
const std::string MAX_NUM_TOKEN = "numbers";
const std::string END_TOKEN = "end";
const std::string ERRORS_OBJECT = "ErrorsObject";
class ErrorsObject: public df::Object
{
private:
	//content of errors object
	std::string content[3];
	///manager object
	ErrorsObjectList * list;
	///difficulty of errors object
	int hardness;
	///color of this
	df::Color color[3];
	///load content from file
	void loadContent();
	///update boundary
	void updateBox();
	///max numbers of errors objects variation
	int max_number;
	bool shift;
	///spawn the object
	void moveToStart();
public:
	ErrorsObject(ErrorsObjectList *n_list, int max_num);
	~ErrorsObject();
	int eventHandler(const df::Event *p_event);
	void draw();
	///remove the letter in the content
	int removeLetter(char c);
	///get Color
	df::Color getColor(int c);
	///get hardness
	int getHardness();
	///set hardness
	void setHardness(int hard);
	///set max number
	void setMaxNumber(int max_num);
	
};
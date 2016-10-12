//this object handle all of the errors object

#pragma once
#include "ObjectList.h"
#include "ErrorsObject.h"
#include <vector>
const std::string ELIST = "elist";
const int LOWEST_HEIGHT = -300;
class ErrorsObject;
class ErrorsObjectList : public df::Object
{
private:
	int highest_gap;
	///highest high
	float max_height;
	///highest object
	ErrorsObject* max_object;
	///control the rate of spawning
	float accelerate;
	float reduction;
	///handling step
	void step(int step_number);
	///errors content
	std::vector<std::string> contents;
	void loadContents();
	bool start = true;
	
public:
	ErrorsObjectList();
	~ErrorsObjectList();
	
	int eventHandler(const df::Event* p_event);
	///get max_height
	float getMaxHeight();
	///set max_height
	void setMaxHeight(float n_height);
	///get max_id
	ErrorsObject* getMaxObject();
	///set max_id
	void setMaxObject(ErrorsObject* n_object);
	///set accelerate
	void setAccelerate(float n_acce);
	///get accelerate
	float getAccelerate();
	///set reduction
	void setReduction(float n_reduc);
	///get reduction
	float getReduction();
	///set highest gap
	void setHighestGap(int n_gap);
	///get highest gap
	int getHighestGap();
	///get contents
	std::string getContents(int num);
	
};
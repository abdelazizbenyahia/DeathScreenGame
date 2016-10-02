#include "Object.h"

class ErrorsObject: public df::Object
{
private:
	const int MAX_NUMBER = 3;
	std::string content;
	ErrorsObjectList * list;
public:
	ErrorsObject();
	~ErrorsObject();
	int eventHandler(const df::Event *p_event);
}
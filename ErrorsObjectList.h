#include "ObjectList.h"
#include "ErrorsObject.h"
class ErrorsObjectList : public df::ObjectList
{
private:
	int max_height;
	int max_index;
public:
	ErrorsObjectList();
	~ErrorsObjectList();
	int delAndUpdate(df::ErrorsObject* p_o);
}
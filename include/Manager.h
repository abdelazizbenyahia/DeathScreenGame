#include "Event.h"
#include <string>
#include <unordered_map>
#include "ObjectList.h"
#pragma once

namespace df
{
const int MAX_EVENTS = 100;
const std::string GENERAL_MANAGER = "df::general_manager";
class Manager
{

private:
    std::string type; /// Manager type identifier.
    bool is_started;  /// True when started successfully.
	std::unordered_map<std::string, ObjectList> event;

protected:
    /// Set type identifier of Manager.
    void setType(std::string type);

public:
    Manager();
    virtual ~Manager();

    /// Get type identifier of Manager.
    std::string getType() const;

    /// Startup Manager.
    /// Return 0 if ok, else negative number.
    virtual int startUp();

    /// Shutdown Manager.
    virtual void shutDown();

    /// Return true when startUp() was executed ok, else false.
    bool isStarted() const;

    /// Send event to all interested Objects.
    /// Return count of number of events sent.

    int onEvent(const Event* e) const;
	///Indicate interest in event
	///return 0 if successful, -1 if not
	int registerInterest(Object *p_o, std::string event_type); 	
	///Remove interest in event
	///return 0 if successful, -1 if not
	int unregisterInterest(Object *p_o, std::string event_type); 

};

} // end of namespace
///
/// The base game world object
///

#pragma once
// System includes.
#include <string>
#include "Vector.h"
#include "Sprite.h"
#include "Box.h"
#include "Event.h"
#include <vector>
#include <string>
namespace df
{
const int MAX_OBJ_EVENT = 30;
enum Solidness {
    HARD,    /// Objects cause collisions and impede.
    SOFT,    /// Objects cause collisions, but don't impede.
    SPECTRAL /// Objects don't cause collisions.
};

class Object
{
private:
    int _ID;                    /// each object has unique ID
    Vector _pos;                /// Vector of object
    float x_velocity;           /// Horizontal speed in spaces per step.
    float y_velocity;           /// Vertical speed in spaces per step.
    std::string _type;          /// user-defined identification
    int altitude;               /// altitude of the object
    Solidness solidness;        /// solidness of the object
    Sprite* p_sprite;           /// Sprite associated with object.
    bool sprite_center;         /// True if sprite centered on object.
    int sprite_index;           /// Current index frame for sprite.
    int sprite_slowdown;        /// Slowdown rate (1 = no slowdown, 0 = stop).
    int sprite_slowdown_count;  /// Slowdown counter.
	char sprite_transparency;   ///< Sprite transparent character (0 if none).
    Box box; /// Box for sprite boundary
	std::vector<std::string> events; /// events that Object interests
	bool is_active;
	

public:
    /// Construct Object.
    /// Set default parameters and add to game world (WorldManager).

    Object();

    /// Destroy Object.
    /// Unregister for any interested events.
    /// Remove from game world (WorldManager).

    virtual ~Object();

    /// Set Object ID
    void setID(int ID);
    /// Set Object Vector
    void setPos(const Vector& pos);
    /// set Object type
    void setType(const std::string& type);
    /// get Object ID
    int getID() const;
    /// Object should draw itself
    const Vector& getPos() const;
    /// get Object type
    const std::string& getType() const;
    /// get the Altitude of the object
    int getAltitude();
    /// set the Altitude of the object
    int setAltitude(int i);
    /// set the solidness of the object
    void setSolidness(Solidness s);
    /// get the solidness of the object
    Solidness getSolidness();
    /// true if HARD or SOFT
    bool isSolid();
    /// Get and set velocity (x,y).
    void setXVelocity(float new_x_velocity);
    float getXVelocity() const;
    void setYVelocity(float new_y_velocity);
    float getYVelocity() const;
    void setVelocity(df::Vector vel);
    Vector getVelocity();
    ///predict position
	Vector predictPosition();
    /// Set object Sprite to new one.
    /// If set_box is true, set bounding box to size of Sprite.
    void setSprite(Sprite* p_new_sprite, bool set_box = true);
    /// Return pointer to Sprite associated with this object.
    Sprite* getSprite() const;
    /// Set Sprite to be centered at object Position (pos).
    void setCentered(bool centered = true);
    /// Indicates if sprite is centered at object Position (pos).
    bool isCentered() const;
    /// Set index of current Sprite frame to be displayed.
    void setSpriteIndex(int new_sprite_index);
    /// Return index of current Sprite frame to be displayed.
    int getSpriteIndex() const;
    /// Slows down sprite animations.
    /// Sprite slowdown is in multiples of GameManager frame time.
    void setSpriteSlowdown(int new_sprite_slowdown);
    int getSpriteSlowdown() const;
    void setSpriteSlowdownCount(int new_sprite_slowdown_count);
    int getSpriteSlowdownCount() const;
    /// Set object's bounding box.
    void setBox(Box new_box);
    /// Get object's bounding box.
    Box getBox() const;
	/// Set Sprite transparency character (0 means none).
	void setTransparency(char transparent=' ');

	/// Get Sprite transparency character (0 means none).
	char getTransparency() const;

    virtual void draw();
    /// get Object Vector

    /// Handle event (default is to ignore everything).
    /// Return 0 if ignored, else 1.
    virtual int eventHandler(const df::Event* p_event);
	///Add interest in event
	///return 0 if successful, -1 if not
	int registerInterest(std::string event_type);
	///Remove interest in event
	///return 0 if successful, -1 if not	
	int unregisterInterest(std::string event_type);	
	///get activeness
	bool isActive();
	///set activeness
	void setIsActive(bool new_active = true);
	///return interested events
	std::vector<std::string> getInterestedEvents();
	
};
}
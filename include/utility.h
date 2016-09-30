#include "EventKeyboard.h"
#include "SFML/Graphics.hpp"
#include "EventMouse.h"
#include "Vector.h"
#include "Box.h"
#include "Object.h"
#include <string>
#pragma once

namespace df
{
/// Return true if two positions intersect, else false.
bool positionsIntersect(df::Vector p1, df::Vector p2);
/// Return true if boxes intersect, else false.
bool boxIntersectsBox(Box A, Box B);
/// Convert relative bounding Box for Object to absolute world Box.
Box getWorldBox(const Object *p_o);
/// Convert relative bounding Box for Object to absolute world Box
/// at Position where.
Box getWorldBox(const Object *p_o, Vector where);// Convert world position to view position.
///convert world position to view position
Vector worldToView(Vector world_pos);
///turn int to string
std::string intToString(int number);

}
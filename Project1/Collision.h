#pragma once
#include "SFML.h"
#include "GameSprite.h"
#include <math.h>

class Line {
public:
	Vector2f point[2];
	Line(Vector2f,Vector2f);
};
class Collision {
public:
	static bool isCollision(const RectangleShape& rect1, const RectangleShape& rect2);
	static bool isCollision(const RectangleShape& rect, const Line& line);
	static bool isCollision(const Line& line1, const Line& line2);
	static bool findShortestCollisionDistance(Vector2f& result, const RectangleShape& rect1, const RectangleShape& rect2);
private:
	static bool inBetween(const float& left, const float& middle, const float& right);
};
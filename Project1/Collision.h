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
	static bool isCollision(RectangleShape rect1, RectangleShape rect2);
	static bool isCollision(RectangleShape rect, Line line);
	static bool isCollision(Line line1, Line line2);
private:
	static bool inBetween(float left, float middle, float right);
};
#pragma once
#include "SFML.h"
#include "GameSprite.h"
#include <math.h>
#include "Dungeon.h"

class Line {
public:
	Vector2f point[2];
	Line(Vector2f, Vector2f);
};
struct Range2f {
	float min = 0, max = 0;
	Range2f();
	Range2f(const float& min,const float& max);
};
class Collision {
public:
	static bool isCollision(const RectangleShape& rect1, const RectangleShape& rect2);
	static bool isCollision(const RectangleShape& rect1, const Range2f& RangeX2, const Range2f& RangeY2);
	static bool isCollision(const RectangleShape& rect, const Line& line);
	static bool isCollision(const RectangleShape& rect, const Vector2f& point);
	static bool isCollision(const Line& line1, const Line& line2);
	static bool isIntercept(const Range2f& range1, const Range2f& range2);
	static bool findShortestCollisionDistance(Vector2f& result, const RectangleShape& rect1, const RectangleShape& rect2);
	static bool findShortestCollisionDistance(Vector2f& result, const RectangleShape& movingRect, const Range2f& XRange, const Range2f& YRange);
	static bool findShortestCollisionDistance(Vector2f& result, const Range2f& moveXRange, const Range2f& moveYRange, const RectangleShape& notMovingRect);
	static bool findShortestCollisionOfPointAtDirection(Vector2f& result, const Vector2f& point, const vector<RectangleShape>& Rects, const Direction& direction);
	static bool inBetween(const float& left, const float& middle, const float& right);
	static bool findIntercept(const Range2f& range1, const Range2f& range2,Range2f& result);
private:
};
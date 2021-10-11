#include "Collision.h"
Range2f::Range2f() :min(0), max(0) {}
Range2f::Range2f(float min, float max) :min(min), max(max) {}
void Range2f::operator *(const Range2f& a) {
	min *= a.min;
	max *= a.max;
}
void Range2f::operator +(const Range2f& a) {
	min += a.min;
	max += a.max;
}
void Range2f::operator -(const Range2f& a) {
	min -= a.min;
	max -= a.max;
}
void Range2f::operator /(const Range2f& a) {
	min /= a.min;
	max /= a.max;
}
void Range2f::operator =(const Range2f& a) {
	min = a.min;
	max = a.max;
}
void Range2f::operator *(const float& a) {
	min *= a;
	max *= a;
}
void Range2f::operator /(const float& a) {
	min /= a;
	max /= a;
}


Vector2f Multiple(const Vector2f& a, const Vector2f& b);
Line::Line(Vector2f p1, Vector2f p2) {
	point[0] = p1;
	point[1] = p2;
}
bool  Collision::inBetween(const float& left,const float& middle,const float& right) {
	if (left <= middle && right >= middle)
		return true;
	return false;
}
bool Collision::isCollision(const RectangleShape& rect1,const RectangleShape& rect2)
{
	Vector2f minRect1 = rect1.getPosition() - Multiple(rect1.getOrigin(), rect1.getScale());
	Vector2f maxRect1 = minRect1 + Multiple(rect1.getSize(), rect1.getScale());
	Vector2f minRect2 = rect2.getPosition() - Multiple(rect2.getOrigin(), rect2.getScale()); ;
	Vector2f maxRect2 = minRect2 + Multiple(rect2.getSize(), rect2.getScale());
	if (maxRect1.x - minRect2.x > 0 && maxRect2.x - minRect1.x > 0)
		if (maxRect1.y - minRect2.y > 0 && maxRect2.y - minRect1.y > 0)
			return true;
	return false;
}
bool Collision::isCollision(const RectangleShape& rect1, const Range2f& RangeX2, const Range2f& RangeY2)
{
	Vector2f minRect1 = rect1.getPosition() - Multiple(rect1.getOrigin(), rect1.getScale());
	Vector2f maxRect1 = minRect1 + Multiple(rect1.getSize(), rect1.getScale());
	Vector2f minRect2(RangeX2.min,RangeY2.max);
	Vector2f maxRect2(RangeX2.max,RangeY2.max);
	if (maxRect1.x - minRect2.x > 0 && maxRect2.x - minRect1.x > 0)
		if (maxRect1.y - minRect2.y > 0 && maxRect2.y - minRect1.y > 0)
			return true;
	return false;
}
bool Collision::isCollision(const RectangleShape& rect,const Line& line)
{
	Vector2f pos1 = rect.getPosition() - Multiple(rect.getOrigin(), rect.getScale());
	Vector2f pos4 = pos1 + Multiple(rect.getSize(), rect.getScale());
	Vector2f pos2(pos1.x, pos4.y);
	Vector2f pos3(pos4.x, pos1.x);
	Line rectLines[4] = { Line(pos1,pos2),Line(pos1,pos3),Line(pos3,pos4),Line(pos2,pos4) };
	for (int i = 0; i < 4; i++) {
		if (isCollision(line, rectLines[i]))
			return true;
	}
}
bool Collision::isCollision(const Line& line1, const Line& line2)
{
	float x1 = line1.point[0].x, x2 = line1.point[1].x, y1 = line1.point[0].y, y2 = line1.point[1].y;
	float m1 = (y2 - y1) / (x2 - x1), c1 = y1 - m1 * x1;
	float x3 = line2.point[0].x, x4 = line2.point[1].x, y3 = line2.point[0].y, y4 = line2.point[1].y;
	float m2 = (y4 - y3) / (x4 - x3), c2 = y3 - m2 * x3;
	if (m1 == m2)
		return false;
	float ansX = (c2 - c1) / (m1 - m2);
	float ansY = m1 * ansX + c1;
	if (abs(x1 - ansX) + abs(x2 - ansX) == abs(x1 - x2) && abs(y1 - ansY) + abs(y2 - ansY) == abs(y1 - y2))
		return true;
}
bool Collision::findShortestCollisionDistance(Vector2f& result,const RectangleShape& movingRect, const RectangleShape& NotMoveRect) {
	Vector2f minRect1 = movingRect.getPosition() - Multiple(movingRect.getOrigin(), movingRect.getScale());
	Vector2f maxRect1 = minRect1 + Multiple(movingRect.getSize(), movingRect.getScale());
	Vector2f minRect2 = NotMoveRect.getPosition() - Multiple(NotMoveRect.getOrigin(), NotMoveRect.getScale()); ;
	Vector2f maxRect2 = minRect2 + Multiple(NotMoveRect.getSize(), NotMoveRect.getScale());
	Vector2f mnDistance;
	bool inBetweenX = false, inBetweenY = false;
	if (!isCollision(movingRect, NotMoveRect))
		return false;
	if (maxRect1.x-minRect2.x< maxRect2.x - minRect1.x) {
		mnDistance.x = maxRect1.x - minRect2.x;
	}
	else {
		mnDistance.x = minRect1.x-maxRect2.x;
	}
	if (maxRect1.y - minRect2.y < maxRect2.y - minRect1.y) {
		mnDistance.y = maxRect1.y - minRect2.y;
	}
	else {
		mnDistance.y =  minRect1.y- maxRect2.y;
	}
	if (abs(mnDistance.x) < abs(mnDistance.y)) {
		mnDistance.y = 0;
		mnDistance.x *= 1.0001;
	}
	else {
		mnDistance.x = 0;
		mnDistance.y *= 1.0001;
	}
	result = -mnDistance;
	return true;
}
bool Collision::findShortestCollisionDistance(Vector2f& result, const RectangleShape& movingRect, const Range2f& NotMoveXRange, const Range2f& NotMoveYRange) {
	Vector2f minRect1 = movingRect.getPosition() - Multiple(movingRect.getOrigin(), movingRect.getScale());
	Vector2f maxRect1 = minRect1 + Multiple(movingRect.getSize(), movingRect.getScale());
	Vector2f minRect2(NotMoveXRange.min,NotMoveYRange.min);
	Vector2f maxRect2(NotMoveXRange.max,NotMoveYRange.max) ;
	Vector2f mnDistance;
	bool inBetweenX = false, inBetweenY = false;
	if (!isCollision(movingRect, NotMoveXRange,NotMoveYRange))
		return false;
	if (maxRect1.x - minRect2.x < maxRect2.x - minRect1.x) {
		mnDistance.x = maxRect1.x - minRect2.x;
	}
	else {
		mnDistance.x = minRect1.x - maxRect2.x;
	}
	if (maxRect1.y - minRect2.y < maxRect2.y - minRect1.y) {
		mnDistance.y = maxRect1.y - minRect2.y;
	}
	else {
		mnDistance.y = minRect1.y - maxRect2.y;
	}
	if (abs(mnDistance.x) < abs(mnDistance.y))
		mnDistance.y = 0;
	else
		mnDistance.x = 0;
	result = -mnDistance;
	return true;
}
bool Collision::findShortestCollisionDistance(Vector2f& result, const Range2f& moveXRange, const Range2f& moveYRange, const RectangleShape& notMovingRect) {
	Vector2f minRect1(moveXRange.min, moveYRange.min); 
	Vector2f maxRect1(moveXRange.max, moveYRange.max);
	Vector2f minRect2 = notMovingRect.getPosition() - Multiple(notMovingRect.getOrigin(), notMovingRect.getScale());
	Vector2f maxRect2 = minRect2 + Multiple(notMovingRect.getSize(), notMovingRect.getScale());
	Vector2f mnDistance;
	bool inBetweenX = false, inBetweenY = false;
	if (!isCollision(notMovingRect, moveXRange, moveYRange))
		return false;
	if (maxRect1.x - minRect2.x < maxRect2.x - minRect1.x) {
		mnDistance.x = maxRect1.x - minRect2.x;
	}
	else {
		mnDistance.x = minRect1.x - maxRect2.x;
	}
	if (maxRect1.y - minRect2.y < maxRect2.y - minRect1.y) {
		mnDistance.y = maxRect1.y - minRect2.y;
	}
	else {
		mnDistance.y = minRect1.y - maxRect2.y;
	}
	if (abs(mnDistance.x) < abs(mnDistance.y))
		mnDistance.y = 0;
	else
		mnDistance.x = 0;
	result = -mnDistance;
	return true;
}
bool Collision::findShortestCollisionOfPointAtDirection(Vector2f& result, const Vector2f& point, const vector<RectangleShape>& Rects, const Direction& direction) {
	float mn = FLT_MAX;
	if (direction == Direction::Right) {
		for (size_t i = 0; i < Rects.size(); i++)
		{
			Vector2f minPos(Rects[i].getPosition().x - Rects[i].getOrigin().x, Rects[i].getPosition().y - Rects[i].getOrigin().y);
			Vector2f maxPos = minPos + Rects[i].getSize();
			if (inBetween(minPos.y, point.y, maxPos.y) && minPos.x > point.x && minPos.x - point.x < mn) {
				mn = minPos.x - point.x;	
			}
		}
		if (mn != FLT_MAX) {
			result = point + Vector2f(mn, 0);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (direction == Direction::Left) {
		for (size_t i = 0; i < Rects.size(); i++)
		{
			Vector2f minPos(Rects[i].getPosition().x - Rects[i].getOrigin().x, Rects[i].getPosition().y - Rects[i].getOrigin().y);
			Vector2f maxPos = minPos + Rects[i].getSize();
			if (inBetween(minPos.y, point.y, maxPos.y) && maxPos.x < point.x && point.x - maxPos.x < mn) {
				mn = point.x - maxPos.x;
			}
		}
		if (mn != FLT_MAX) {
			result = point + Vector2f(-mn, 0);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (direction == Direction::Down) {
		for (size_t i = 0; i < Rects.size(); i++)
		{
			Vector2f minPos(Rects[i].getPosition().x - Rects[i].getOrigin().x, Rects[i].getPosition().y - Rects[i].getOrigin().y);
			Vector2f maxPos = minPos + Rects[i].getSize();
			if (inBetween(minPos.x, point.x, maxPos.x) && minPos.y > point.y && minPos.y-point.y < mn) {
				mn = minPos.y - point.y;
			}
		}
		if (mn != FLT_MAX) {
			result = point + Vector2f(0, mn);
			return true;
		}
		else
		{
			return false;
		}
	}
	else {
		for (size_t i = 0; i < Rects.size(); i++)
		{
			Vector2f minPos(Rects[i].getPosition().x - Rects[i].getOrigin().x, Rects[i].getPosition().y - Rects[i].getOrigin().y);
			Vector2f maxPos = minPos + Rects[i].getSize();
			if (inBetween(minPos.x, point.x, maxPos.x) && maxPos.y < point.y && point.y - maxPos.y < mn) {
				mn = point.y - maxPos.y;
			}
		}
		if (mn != FLT_MAX) {
			result = point + Vector2f(0, -mn);
			return true;
		}
		else
		{
			return false;
		}
	}
}

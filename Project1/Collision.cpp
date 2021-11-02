#include "Collision.h"
#include < algorithm >
Range2f::Range2f() :min(0), max(0) {}
Range2f::Range2f(const float& point1,const float& point2) :min(std::min(point1, point2)), max(std::max(point1,point2)) {  }



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
	Vector2f minRect1 = rect1.getPosition() -rect1.getOrigin();
	Vector2f maxRect1 = minRect1 + rect1.getSize();
	Vector2f minRect2 = rect2.getPosition() - rect2.getOrigin() ;
	Vector2f maxRect2 = minRect2 + rect2.getSize();
	if (maxRect1.x - minRect2.x > 0 && maxRect2.x - minRect1.x > 0)
		if (maxRect1.y - minRect2.y > 0 && maxRect2.y - minRect1.y > 0)
			return true;
	return false;
}
bool Collision::isCollision(const RectangleShape& rect1, const Range2f& RangeX2, const Range2f& RangeY2)
{
	Vector2f minRect1 = rect1.getPosition() - rect1.getOrigin();
	Vector2f maxRect1 = minRect1 + rect1.getSize();
	Vector2f minRect2(RangeX2.min,RangeY2.max);
	Vector2f maxRect2(RangeX2.max,RangeY2.max);
	if (maxRect1.x - minRect2.x > 0 && maxRect2.x - minRect1.x > 0)
		if (maxRect1.y - minRect2.y > 0 && maxRect2.y - minRect1.y > 0)
			return true;
	return false;
}
bool Collision::isCollision(const RectangleShape& rect,const Line& line)
{
	Vector2f minRect = rect.getPosition() - rect.getOrigin();
	Vector2f maxRect = minRect + rect.getSize();
	Range2f rangeX,rangeY;
	float deltaY = line.point[1].y - line.point[0].y, deltaX = line.point[1].x - line.point[0].x;
	if (findIntercept(Range2f(minRect.x, maxRect.x), Range2f(line.point[0].x, line.point[1].x), rangeX)) {
		rangeY = Range2f(line.point[0].x + (rangeX.min - minRect.x) * deltaY / deltaX, line.point[0].x + (rangeX.max - minRect.x) * deltaY / deltaX);
		if (isIntercept(Range2f(minRect.y, maxRect.y), Range2f(rangeY.min, rangeY.max))) {
			return true;
		}
	}
	return false;
}
bool Collision::isCollision(const RectangleShape& rect, const Vector2f& point)
{
	Vector2f minRect = rect.getPosition() - rect.getOrigin();
	Vector2f maxRect = minRect + rect.getSize();
	if (inBetween(minRect.x, point.x, maxRect.x) && inBetween(minRect.y, point.y, maxRect.y))
		return true;
	else
		return false;
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
		mnDistance.x *= (float)1.0001;
	}
	else {
		mnDistance.x = 0;
		mnDistance.y *= (float)1.0001;
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
		float sizeX;
		for (size_t i = 0; i < Rects.size(); i++)
		{
			Vector2f minPos(Rects[i].getPosition().x - Rects[i].getOrigin().x, Rects[i].getPosition().y - Rects[i].getOrigin().y);
			Vector2f maxPos = minPos + Rects[i].getSize();
			if (inBetween(minPos.y, point.y, maxPos.y) && minPos.x > point.x && minPos.x - point.x < mn) {
				mn = minPos.x - point.x;	
				sizeX = (maxPos.x - minPos.x)/2;
			}
		}
		if (mn != FLT_MAX) {
			result = point + Vector2f(mn+sizeX, 0);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (direction == Direction::Left) {
		float sizeX;
		for (size_t i = 0; i < Rects.size(); i++)
		{
			Vector2f minPos(Rects[i].getPosition().x - Rects[i].getOrigin().x, Rects[i].getPosition().y - Rects[i].getOrigin().y);
			Vector2f maxPos = minPos + Rects[i].getSize();
			if (inBetween(minPos.y, point.y, maxPos.y) && maxPos.x < point.x && point.x - maxPos.x < mn) {
				mn = point.x - maxPos.x;
				sizeX = (maxPos.x - minPos.x)/2;
			}
		}
		if (mn != FLT_MAX) {
			result = point + Vector2f(-mn-sizeX, 0);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (direction == Direction::Down) {
		float sizeY;
		for (size_t i = 0; i < Rects.size(); i++)
		{
			Vector2f minPos(Rects[i].getPosition().x - Rects[i].getOrigin().x, Rects[i].getPosition().y - Rects[i].getOrigin().y);
			Vector2f maxPos = minPos + Rects[i].getSize();
			if (inBetween(minPos.x, point.x, maxPos.x) && minPos.y > point.y && minPos.y-point.y < mn) {
				mn = minPos.y - point.y;
				sizeY = (maxPos.y - minPos.y)/2;
			}
		}
		if (mn != FLT_MAX) {
			result = point + Vector2f(0, mn+sizeY);
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
bool Collision::isIntercept(const Range2f& range1, const Range2f& range2) {
	float min=std::max(range1.min,range2.min) , max=std::min(range1.max,range1.min);
	return min < max;
}
bool Collision::findIntercept(const Range2f& range1, const Range2f& range2,Range2f& result) {
	float min = std::max(range1.min, range2.min), max = std::min(range1.max, range1.min);
	if (min < max) {
		result = Range2f(min, max);
		return true;
	}
	return false;
}

float Collision::findDisTance(const Vector2f& pos1, const Vector2f& pos2)
{
	Vector2f distance2=pos1-pos2;
	return sqrt(pow(distance2.x,2)+ pow(distance2.y,2)) ;
}

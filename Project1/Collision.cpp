#include "Collision.h"
#include <iostream>
Vector2f Multiple(Vector2f a, Vector2f b);
Line::Line(Vector2f p1, Vector2f p2) {
	point[0] = p1;
	point[1] = p2;
}
bool Collision::isCollision(RectangleShape rect1, RectangleShape rect2)
{
	Vector2f pos1 = rect1.getPosition() - Multiple(rect1.getOrigin(), rect1.getScale());
	Vector2f pos2 = pos1 + Multiple(rect1.getSize(), rect1.getScale());
	Vector2f pos3 = rect2.getPosition() -Multiple(rect2.getOrigin(), rect2.getScale()); ;
	Vector2f pos4 = pos3 + Multiple(rect2.getSize(), rect2.getScale());
	if ((pos1.x >= pos3.x && pos1.x <= pos4.x) || (pos2.x >= pos3.x && pos2.x <= pos4.x))
		if ((pos1.y >= pos3.y && pos1.y <= pos4.y) || (pos2.y >= pos3.y && pos2.y <= pos4.y))
			return true;
	return false;
}
bool Collision::isCollision(RectangleShape rect, Line line)
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
bool Collision::isCollision(Line line1, Line line2)
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
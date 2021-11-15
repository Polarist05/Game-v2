#pragma once
#include "KnifeInteractable.h"
#include "Tile.h"
class MoveableBlockClass:public Area, public KnifeInteractable
{
	Vector2i blockPosition;
	Vector2f velocity;
	Vector2f lastPosition;
	bool isMove=false;
public:
	void SetPosition(const Vector2i& v);
	MoveableBlockClass();
	MoveableBlockClass(std::string s);
	bool PushBlock(const Direction& direction);
	void interacting(weak_ptr<Knife> knife) override;
	void Update() override;
};


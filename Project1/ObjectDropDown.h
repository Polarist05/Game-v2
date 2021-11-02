#pragma once
#include "ClickableSprite.h"
#include "Room.h"
class ObjectDropDown :public ClickableSprite
{
	int saveInt;
public:
	void Activate()override;
	void(*func)(Vector2i pos);
	void SetType(const ObjectType& obj);
};


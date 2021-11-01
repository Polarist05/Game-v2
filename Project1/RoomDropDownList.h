#pragma once
#include "ClickableSprite.h"
class RoomDropDownList : public ClickableSprite
{
public:
	int index;
	std::string name;
	void Activate() override;
};


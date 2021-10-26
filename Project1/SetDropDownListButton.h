#pragma once
#include "ClickableSprite.h"
class SetDropDownListButton : public ClickableSprite
{
public:
	int index;
	std::string name;
	void Activate() override;
};


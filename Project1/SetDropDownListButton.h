#pragma once
#include "ClickableSprite.h"
class SetDropDownListButton : public ClickableSprite
{
public:
	std::string name;
	void Activate() override;
};


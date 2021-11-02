#pragma once
#include "ClickableSprite.h"
class FloorButton:public ClickableSprite
{
public:
	FloorButton();
	FloorButton(std::string s);
	void Activate() override;
};


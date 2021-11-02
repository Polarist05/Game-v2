#pragma once
#include "ClickableSprite.h"
class CliffButton:public ClickableSprite
{
public:
	CliffButton();
	CliffButton(std::string s);
	void Activate() override;
};


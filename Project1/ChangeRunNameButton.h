#pragma once
#include "ClickableSprite.h"
class ChangeRunNameButton:public ClickableSprite
{
public:
	ChangeRunNameButton();
	ChangeRunNameButton(std::string s);
	virtual void Activate();
};


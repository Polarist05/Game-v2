#pragma once
#include "GameSprite.h"
class ClickableSprite:public GameSprite
{
public:
	ClickableSprite();
	ClickableSprite(std::string s);
	virtual void Activate();
};


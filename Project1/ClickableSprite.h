#pragma once
#include "GameSprite.h"
class ClickableSprite:public GameSprite
{
public:
	virtual void CheckClick();
	virtual void Activate();
};


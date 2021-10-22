#pragma once
#include "ClickableSprite.h"
class PlayButton:public ClickableSprite
{
public:
	void CheckClick() override;
	void Activate() override;
};


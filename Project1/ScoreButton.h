#pragma once
#include "ClickableSprite.h"
class ScoreButton:public ClickableSprite
{
public:
	void CheckClick() override;
	void Activate() override;
};


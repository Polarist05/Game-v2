#pragma once
#include "ClickableSprite.h"
class ChoosingEdge:public ClickableSprite
{
public:
	Direction direction;
	void Activate()override;
};


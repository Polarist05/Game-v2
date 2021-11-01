#pragma once
#include "ClickableSprite.h"
class ChoosingEdge:public ClickableSprite
{
	Color color;
public:
	const Color GetColor();
	void SetColor(const Color& color);
	Direction direction;
	void Activate()override;
};


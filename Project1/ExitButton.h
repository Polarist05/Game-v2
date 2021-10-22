#pragma once
#include "ClickableSprite.h"
class ExitButton:public ClickableSprite
{
public:
	void CheckClick() override;
	void Activate() override;
};


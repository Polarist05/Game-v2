#pragma once
#include "ClickableSprite.h"
class ToolkitButton:public ClickableSprite
{
public:
	void CheckClick() override;
	void Activate() override;
};


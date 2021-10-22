#pragma once
#include "ClickableSprite.h"
class SettingButton:public ClickableSprite
{
public:
	void CheckClick() override;
	void Activate() override;
};


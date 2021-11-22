#pragma once
#include "ClickableSprite.h"
class CharClickSprite:public ClickableSprite
{
	int index;
public:
	CharClickSprite();
	CharClickSprite(std::string s);
	void Setup(const int& index);
	void Activate()override;
};


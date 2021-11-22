#include "CharClickSprite.h"

CharClickSprite::CharClickSprite():ClickableSprite(){}

CharClickSprite::CharClickSprite(std::string s):ClickableSprite(s){}

void CharClickSprite::Setup(const int& index)
{
	this->index = index;
}

void CharClickSprite::Activate()
{
}

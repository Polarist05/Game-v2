#include "ClickableSprite.h"

ClickableSprite::ClickableSprite():GameSprite(){}
ClickableSprite::ClickableSprite(std::string s):GameSprite(s) {}

void ClickableSprite::Activate(){ printf("this is ClickableSprite\n"); }
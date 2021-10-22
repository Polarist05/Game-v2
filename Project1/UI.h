#pragma once
#include "ClickableSprite.h"
enum UIType
{
	StartUI,
};
class UI
{
public:
	void SetVisible(bool b);
	vector<weak_ptr<ClickableSprite> > clickableSprites;
	vector<weak_ptr<GameSprite> > NormalSprites;
};


#pragma once
#include "ClickableSprite.h"
enum UIType
{
	StartPage,ToolkitPage
};
class UI
{
public:
	void SetVisible(bool b);
	vector<weak_ptr<ClickableSprite> > clickableTextureSprites;
	vector<weak_ptr<GameSprite> > NormalSprites;
	vector<weak_ptr<GameSprite> > NormalSprites2;
};


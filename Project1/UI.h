#pragma once
#include "ClickableSprite.h"
enum UIType
{
	StartPage,ToolkitPage,EndGamePage
};
class UI
{
public:
	static void CheckUICollision();
	void SetVisible(bool b);
	vector<weak_ptr<ClickableSprite> > clickableSprites;
	vector<weak_ptr<GameSprite> > NormalSprites;
	vector<weak_ptr<GameSprite> > NormalSprites2;
};


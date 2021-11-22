#pragma once
#include "TextUI.h"
#include "ClickableSprite.h"
#include "charClickSprites.h"
class choosedGroupList
{
public:
	choosedGroupList();
	TextUI indexText;
	charClickSprites clickSprites;
	weak_ptr<GameSprite> background;
	void SetPosition(const Vector2f& v);
	void SetParent(const weak_ptr<GameSprite>& wp);
	void SetVisible(const bool& b);
	//vector<weak_ptr<GameSprite> >& getSprites();
	void Release();
};


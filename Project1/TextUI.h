#pragma once
#include "GameSprite.h"
class TextUI 
{
	vector<weak_ptr<GameSprite> > charlist;
	Vector2f position;
public:	
	TextUI();
	Vector2f GetPosition();
	void SetText(const std::string& s);
	void SetPosition(const Vector2f& v);
	void SetParent(const weak_ptr<GameSprite>& wp);
	void SetColor(const Color& b);
	vector<weak_ptr<GameSprite> >& getSprites();
	void Release();
	
};


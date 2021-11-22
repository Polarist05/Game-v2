#pragma once
#include "CharClickSprite.h"
class charClickSprites
{
	vector<weak_ptr<CharClickSprite > > spritelist;
	Vector2f position;
public:
	charClickSprites();
	Vector2f GetPosition();
	void SetTexture(Texture* s);
	void SetPosition(const Vector2f& v);
	void SetParent(const weak_ptr<GameSprite>& wp);
	void SetColor(const Color& color);
	vector<weak_ptr<CharClickSprite> >& getSprites();
	void Release();
};


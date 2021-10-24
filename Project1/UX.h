#pragma once
#include "GameSprite.h"
class UX
{
	Texture keyTexture[2];
	Texture soulTexture[2];
public:
	UX(const int& keyAmount,const int& soulAmount);
	void SetSoul(const int& amount);
	void SetKey(const int& amount);
	vector<weak_ptr<GameSprite> > keys;
	vector<weak_ptr<GameSprite> > souls;
};


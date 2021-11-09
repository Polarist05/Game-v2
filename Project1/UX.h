#pragma once
#include "GameSprite.h"
#include "TextUI.h"
class UX :public GameBaseClass
{
	Texture keyTexture[2];
	Texture soulTexture[2];
	void SetSoul(const int& amount);
	void SetKey(const int& amount);
public:
	UX();
	vector<weak_ptr<GameSprite> > keys;
	vector<weak_ptr<GameSprite> > souls;
	RectangleShape scoreHighlight;
	RectangleShape runTimeHighlight;
	TextUI score;
	TextUI runTime;
	void Update()override;
};


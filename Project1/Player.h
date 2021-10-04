#pragma once
#include "SFML.h"
#include "GameSprite.h"
class Player :public GameSprite
{
protected:
	RenderWindow& window();
public:
	Player(std::string s);
	void Start() override {
	}
	void Update() override;
};
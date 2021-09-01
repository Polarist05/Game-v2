#pragma once
#pragma once
#include "SFML.h"
#include "GameBaseClass.h"
#include "WorldControl.h"
class Player :public GameBaseClass
{
public:
	RectangleShape& Sprite();
	void Start() override {
		Sprite().setSize(Vector2f(50, 50));
		Sprite().setOrigin(Sprite().getSize().x / 2, Sprite().getSize().y / 2);
		Sprite().setFillColor(Color::Green);
		Sprite().setPosition(-460, 0);
	}
	void Update() override {
		WorldControl::window().draw(Sprite());
	}
};
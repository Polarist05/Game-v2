#pragma once
#include "SFML.h"
#include "GameBaseClass.h"
#include "GameSprite.h"
class Player :public GameSprite
{
protected:
	RenderWindow& window();
public:
	Player(std::string s);
	void Start() override {
		transform->renderBox.setSize(Vector2f(50, 50));
		transform->renderBox.setOrigin(transform->renderBox.getSize().x / 2, transform->renderBox.getSize().y / 2);
		transform->renderBox.setFillColor(Color::Green);
		transform->renderBox.setPosition(-460, 0);
		transform->hitBox.setSize(Vector2f(100, 100));
		transform->hitBox.setOrigin(transform->hitBox.getSize().x / 2, transform->hitBox.getSize().y / 2);
		transform->hitBox.setFillColor(Color::Magenta);
		transform->hitBox.setPosition(-460, 0);
	}
	void Update() override {
		//window().draw(transform.hitBox);
		//window().draw(transform.renderBox);
	}
};
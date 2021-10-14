#pragma once
#define THROWING_SPEED 5
#include "GameSprite.h"
class Knife:public GameSprite
{
	Vector2f velocity;
	Direction direction;
	bool isStop = false;
public:
	clock_t startCollisionTimeWithPortal = 0;
	
	void Start() override;
	void Update() override;
	const bool& GetIsStop();
	void Stop();
	
};


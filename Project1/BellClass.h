#pragma once
#include "MeleeAttackable.h"
#include "Tile.h"
#include <set>
#define RING_DURATION 2000
class BellClass:public Area,public MeleeAttackable
{
	bool isActivate=false;
	clock_t StartActivateTime=0;
public:
	std::set<GameTransform*> lastFrameCollisionObjects;
	BellClass();
	BellClass(std::string s);
	weak_ptr<GameSprite> ringArea=Instantiate<GameSprite>("RingArea");
	void MeleeAttackActivate()override;
	void Update()override;
	void Start()override;
};


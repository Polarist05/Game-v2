#pragma once
#include "MeleeAttackable.h"
#include "KnifeInteractable.h"
#include "Tile.h"
#include "Input.h"
#include <set>
#define RING_DURATION 2000
class BellClass :public Input, public MeleeAttackable, public KnifeInteractable
{
	bool isActivate=false;
	clock_t StartActivateTime=0;
public:
	std::set<GameTransform*> lastFrameCollisionObjects;
	BellClass();
	BellClass(std::string s);
	weak_ptr<GameSprite> ringArea=Instantiate<GameSprite>("RingArea");
	void interacting(weak_ptr<Knife> knife)override;
	void MeleeAttackActivate()override;
	void ActivateRinging ();
	void Update()override;
	void Start()override;
};


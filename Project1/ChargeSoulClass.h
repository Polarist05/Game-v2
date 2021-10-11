#pragma once
#include "Tile.h"
#include "MeleeAttackable.h"
class ChargeSoulClass:public Area,public MeleeAttackable
{
	bool wasUsed = false;
public:
	ChargeSoulClass(std::string s);
	ChargeSoulClass();
	void MeleeAttackActivate()override;
};


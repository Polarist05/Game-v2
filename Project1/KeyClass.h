#pragma once
#include "Tile.h"
#include "Walkable.h"
class KeyClass :public Walkable, public Area
{
public:
	KeyClass();
	KeyClass(std::string s);
	void WalkThroughActivate()override;
};


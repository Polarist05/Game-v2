#pragma once
#include "Tile.h"
#include "Walkable.h"
class StrawberryClass :public Walkable, public Area
{
public:
	StrawberryClass();
	StrawberryClass(std::string s);
	void WalkThroughActivate()override;
};


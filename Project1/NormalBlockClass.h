#pragma once
#include "Tile.h"
#include "KnifeInteractable.h"
class NormalBlockClass:public Area,public KnifeInteractable
{
public:
	NormalBlockClass();
	NormalBlockClass(std::string s);
	void interacting(weak_ptr<Knife> knife) override;
};


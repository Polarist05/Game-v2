#pragma once
#include "Tile.h"
#include "KnifeInteractable.h"
class DeleteBlockClass:public Area,public KnifeInteractable
{
public:
	DeleteBlockClass();
	DeleteBlockClass(std::string s);
	void interacting(weak_ptr<Knife> knife) override;
};


#pragma once
#include "Tile.h"
#include "Walkable.h"
#include "KnifeInteractable.h"
class PortalClass:public Area,public Walkable,public KnifeInteractable
{
	Uint32 lastCollisionTime =0;
public:
	weak_ptr<PortalClass> pairPortal;
	PortalClass();
	PortalClass(std::string s);
	void WalkThroughActivate()override;
	bool Linking(weak_ptr<PortalClass> pairPortal);
	void interacting(weak_ptr<Knife> knife) override;
};


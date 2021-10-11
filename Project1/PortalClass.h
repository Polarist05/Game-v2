#pragma once
#include "Tile.h"
#include "Walkable.h"
class PortalClass:public Area,public Walkable
{
	Uint32 lastCollisionTime =0;
public:
	weak_ptr<PortalClass> pairPortal;
	PortalClass();
	PortalClass(std::string s);
	void WalkThroughActivate()override;
	bool Linking(weak_ptr<PortalClass> pairPortal);
};


#pragma once
#include "Knife.h"
class KnifeInteractable
{
public:
	void virtual interacting(weak_ptr<Knife> knife)=0;
};


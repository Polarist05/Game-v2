#pragma once
#include "Input.h"
#include "KnifeInteractable.h"
#include "MeleeAttackable.h"
class SwitchClass:public Input,public KnifeInteractable,public MeleeAttackable
{
	void Fliping();
public:
	SwitchClass();
	SwitchClass(std::string s);
	void interacting(weak_ptr<Knife> knife)override;
	void MeleeAttackActivate()override;
};


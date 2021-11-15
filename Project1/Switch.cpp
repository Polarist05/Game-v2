#include "SwitchClass.h"

void SwitchClass::Fliping()
{
	TurnOn(!GetIsOn());
}

SwitchClass::SwitchClass():Input(){}

SwitchClass::SwitchClass(std::string s):Input(s){}

void SwitchClass::interacting(weak_ptr<Knife> knife)
{
	auto index = knife.lock()->transform->typeIndex;
	auto wp = knife.lock()->transform->wp;
	Destroy(wp, index);
	Fliping();
}

void SwitchClass::MeleeAttackActivate()
{
	Fliping();
}

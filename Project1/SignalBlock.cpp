#include "SignalBlockClass.h"

SignalBlockClass::SignalBlockClass():Output(){}

SignalBlockClass::SignalBlockClass(std::string s):Output(s){}

void SignalBlockClass::TurnOn(const bool& b)
{
	Output::TurnOn(b);
	transform->renderBox.setFillColor(!b?Color::White:Color::Transparent);
}

void SignalBlockClass::interacting(weak_ptr<Knife> knife)
{
	if (!GetIsOn()) {
		Vector2f newPos = knife.lock()->transform->GetRealposition() - transform->GetRealposition();
		knife.lock()->transform->position = newPos;
		knife.lock()->transform->SetParent(transform->wp);
		knife.lock()->Stop();
	}
}

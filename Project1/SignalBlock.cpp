#include "SignalBlockClass.h"

SignalBlockClass::SignalBlockClass():Output(){}

SignalBlockClass::SignalBlockClass(std::string s):Output(s){}

void SignalBlockClass::TurnOn(const bool& b)
{
	if (b)
	{
		for (auto& wp : knifeChilds)
		{
			if (!wp.expired())
			{
				auto wp1 = wp.lock()->transform->wp;
				auto index = wp.lock()->transform->typeIndex;
				Destroy(wp1, index);
			}
		}
		knifeChilds.clear();
	}
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
		knifeChilds.push_back(knife);
	}
}

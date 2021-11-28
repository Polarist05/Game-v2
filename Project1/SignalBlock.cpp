#include "SignalBlockClass.h"
#include "WorldControl.h"
SignalBlockClass::SignalBlockClass():Output(){}

void SignalBlockClass::Update()
{
	Vector2i pos = GetTransform()->GetPositionInTilemap();
	if (isWait&&!WControl::GetCurrentRoom().lock()->cannotPush[pos.y][pos.x])
	{
		WControl::GetCurrentRoom().lock()->cannotPush[pos.y][pos.x] = true;
		transform->renderBox.setFillColor(Color::White);
		isWait = false;
	}
}

SignalBlockClass::SignalBlockClass(std::string s):Output(s){}

void SignalBlockClass::TurnOn(const bool& b)
{
	Vector2i pos = GetTransform()->GetPositionInTilemap();
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
		WControl::GetCurrentRoom().lock()->cannotPush[pos.y][pos.x]=false;
		transform->renderBox.setFillColor(Color::Transparent);
		isWait = false;
	}
	else if(!WControl::GetCurrentRoom().lock()->cannotPush[pos.y][pos.x])
	{
		WControl::GetCurrentRoom().lock()->cannotPush[pos.y][pos.x] = true;
		transform->renderBox.setFillColor(Color::White);
	}
	else
	{
		isWait = true;
	}
	Output::TurnOn(b);
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

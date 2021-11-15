#pragma once
struct SwitchGroup;
#include "Tile.h"
class Input:public Area
{
	bool isOn=false;
	SwitchGroup* m_switchGroup;
public:
	Input();
	Input(std::string s);
	bool GetIsOn();
	void Setup(SwitchGroup* switchGroup);
	void TurnOn(const bool& b);
};


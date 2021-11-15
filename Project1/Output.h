#pragma once
struct SwitchGroup;
#include "Tile.h"
class Output:public Area
{
	bool isOn = false;
	SwitchGroup* m_switchGroup;
public:
	Output();
	Output(std::string s);
	bool GetIsOn();
	void Setup(SwitchGroup* switchGroup);
	virtual void TurnOn(const bool& b);
};


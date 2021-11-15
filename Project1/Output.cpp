#include "Output.h"
#include "Room.h"
Output::Output():Area(){}
Output::Output(std::string s):Area(s){}
bool Output::GetIsOn()
{
	return isOn;
}
void Output::Setup(SwitchGroup* switchGroup)
{
	m_switchGroup = switchGroup;
	m_switchGroup->outputs.push_back(dynamic_pointer_cast<Output>(transform->wp.lock()));
}

void Output::TurnOn(const bool& b)
{
	isOn = b;
}

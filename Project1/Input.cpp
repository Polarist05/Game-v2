#include "Input.h"
#include "Output.h"
#include "Room.h"

Input::Input():Area(){}

Input::Input(std::string s):Area(s){}

bool Input::GetIsOn()
{
	return isOn;
}

void Input::Setup(SwitchGroup* switchGroup)
{
	m_switchGroup = switchGroup;
	m_switchGroup->input = dynamic_pointer_cast<Input>(transform->wp.lock()) ;
}

void Input::TurnOn(const bool& b)
{
	isOn = b;
	for (auto& wp : m_switchGroup->outputs) {
		printf("In");
		wp.lock()->TurnOn(b);
	}
}

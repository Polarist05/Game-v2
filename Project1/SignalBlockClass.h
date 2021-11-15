#pragma once
#include "Output.h"
#include "KnifeInteractable.h"
class SignalBlockClass:public Output,public KnifeInteractable
{
public:
	SignalBlockClass();
	SignalBlockClass(std::string s);
	void TurnOn(const bool& b)override;
	void interacting(weak_ptr<Knife> wp) override;
};


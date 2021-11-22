#pragma once
#include "Output.h"
#include "KnifeInteractable.h"
class SignalBlockClass:public Output,public KnifeInteractable
{
public:
	SignalBlockClass();
	SignalBlockClass(std::string s);
	vector<weak_ptr<Knife>> knifeChilds;
	void TurnOn(const bool& b)override;
	void interacting(weak_ptr<Knife> wp) override;
};


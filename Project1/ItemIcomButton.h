#pragma once
#include "ClickableSprite.h"
#include "ObjectDropDown.h"
class ItemIcomButton:public ClickableSprite
{
public:
	void Activate() override;
	void Start() override;
	vector<weak_ptr<ObjectDropDown> >  objectDropDowns;
};


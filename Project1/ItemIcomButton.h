#pragma once
#include "ClickableSprite.h"
#include "ObjectDropDown.h"
#include "FloorButton.h"
#include "CliffButton.h"
class ItemIconButton:public ClickableSprite
{
public:
	void Activate() override;
	void Start() override;
	vector<weak_ptr<ObjectDropDown> >  objectDropDowns;
	weak_ptr<CliffButton> cliffButton;
	weak_ptr<FloorButton> floorButton;
	void Setup();
};


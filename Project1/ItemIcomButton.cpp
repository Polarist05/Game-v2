#include "ItemIcomButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"
void ItemIcomButton::Activate()
{
}

void ItemIcomButton::Start()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	/*
	int i = 1;
	for (auto& wp : WControl::objectsPrefab()) {
		objectDropDowns.push_back(Instantiate<ObjectDropDown>());
		objectDropDowns.rbegin()->lock()->transform->renderBox.setTexture(&wp.second);
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(190, 250), Vector2f(190, 250), Vector2f(0, 0), Vector2f(0, 0), 0.3);
		objectDropDowns.rbegin()->lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		objectDropDowns.rbegin()->lock()->transform->SetParent(transform->wp);
		objectDropDowns.rbegin()->lock()->transform->SetPosition(Vector2f(i * 80,0));

		thisUI.clickableTextureSprites.push_back(*objectDropDowns.rbegin());
		i++;
	}*/
}

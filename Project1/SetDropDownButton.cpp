#include "SetDropDownButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"
#include <iostream>
void SetDropDownButton::InstantList()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	for (int i = 0; i < 10; i++) {
		weak_ptr<GameSprite> wp = Instantiate<GameSprite>();
		
		wp.lock()->transform->SetPosition(Vector2f(-transform->renderBox.getSize().x / 2 + wp.lock()->transform->renderBox.getSize().x * (i + 1.5), 0));
		thisUI.NormalSprites2.push_back(wp);
	}
	for (int i = 0; i < 10; i++) {
		weak_ptr<SetDropDownListButton> wp = Instantiate<SetDropDownListButton>();
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["TaskBar"]);
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(transform->wp);
		wp.lock()->transform->SetPosition(Vector2f(0, 45 * (i + 1)));
		thisUI.clickableTextureSprites.push_back(wp);
		thisUI.NormalSprites2.push_back(wp);
		dropDownList.push_back(wp);

		textDropDown.push_back(TextUI());
		textDropDown.rbegin()->SetColor(Color::Transparent);
		textDropDown.rbegin()->SetParent(wp);
		for (auto& wp1 : textDropDown.rbegin()->getSprites()){
			thisUI.NormalSprites2.push_back(wp1);
		}
	}
	UpdateText();
}
SetDropDownButton::SetDropDownButton() :ClickableSprite() {}
SetDropDownButton::SetDropDownButton(string s) : ClickableSprite(s) {}
void SetDropDownButton::Open()
{
	ToolkitUI& thisUI = *(ToolkitUI*)WControl::AllUI()[UIType::ToolkitPage];
	for (auto wp : dropDownList) {
		wp.lock()->transform->renderBox.setFillColor(Color::White);
	}
	for (auto& texts : textDropDown) {
		texts.SetColor(Color::White);
	}
	thisUI.dropDown2.lock()->choosedText.SetColor(Color::Transparent);
	{
		thisUI.newRoomButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.newSetButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.dropDown2.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.deleteSetButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
	}
	isOpen = true;
}
void SetDropDownButton::Close()
{
	ToolkitUI& thisUI = *(ToolkitUI*)WControl::AllUI()[UIType::ToolkitPage];
	for (auto wp : dropDownList) {
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
	}
	for (auto texts : textDropDown) {
		texts.SetColor(Color::Transparent);
	}
	thisUI.dropDown2.lock()->choosedText.SetColor(Color::White);
	{
		thisUI.newRoomButton.lock()->transform->renderBox.setFillColor(Color::White);
		thisUI.newSetButton.lock()->transform->renderBox.setFillColor(Color::White);
		thisUI.dropDown2.lock()->transform->renderBox.setFillColor(Color::White);
		thisUI.deleteSetButton.lock()->transform->renderBox.setFillColor(Color::White);
	}
	isOpen = false;
}
void SetDropDownButton::UpdateText()
{
	ToolkitUI& thisUI = *(ToolkitUI*)WControl::AllUI()[UIType::ToolkitPage];	
	choosedText.SetText(thisUI.choosingSet); 
	int i = 0;
	for (auto& roomSet : WControl::allRoomPrefabs()) {
		if (i < 10) {
			dropDownList[i].lock()->name = roomSet.first;
			textDropDown[i].SetText(roomSet.first);
			textDropDown[i].SetColor(Color::Transparent);
			
		}
		i++;
	}
	for (; i < 10; i++) {
		dropDownList[i].lock()->name = "";
		textDropDown[i].SetText("");
	}
}
void SetDropDownButton::Activate() {
	ToolkitUI& thisUI = *(ToolkitUI*)WControl::AllUI()[UIType::ToolkitPage];
	if (!thisUI.dropDown2.lock()->isOpen) { 
		if (!isOpen)
			Open();
		else
			Close();
	}
}

void SetDropDownButton::SetAllVisible(const bool& b)
{
	if (!b) {
		transform->renderBox.setFillColor(Color::Transparent);
		for (auto& a : dropDownList) {
			a.lock()->transform->renderBox.setFillColor(Color::Transparent);
		}
		for (auto& a : textDropDown) {
			a.SetColor(Color::Transparent);
		}
		choosedText.SetColor(Color::Transparent);
	}
	else {
		transform->renderBox.setFillColor(Color::White);
		choosedText.SetColor(Color::White);

	}
}

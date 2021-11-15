#include "RoomDropDownButton.h"
#include "RoomDropDownList.h"
#include "NextRoomButton.h"
#include "PreviousRoomButton.h"
#include "ToolkitUI.h"
#include "WorldControl.h"
#include <iostream>
RoomDropDownButton::RoomDropDownButton():ClickableSprite(){}
RoomDropDownButton::RoomDropDownButton(std::string s):ClickableSprite(s){}
void RoomDropDownButton::InstantList()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	
	choosedText.SetColor(Color::White);
	choosedText.SetParent(transform->wp);
	for(auto& wp:choosedText.getSprites())
		thisUI.NormalSprites2.push_back(wp);
	for (int i = 0; i < 8; i++) {
		weak_ptr<RoomDropDownList> wp = Instantiate<RoomDropDownList>();
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["TaskBar"]);
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(transform->wp);
		wp.lock()->transform->SetPosition(Vector2f(0, 45 * (i + 1)));
		thisUI.clickableSprites.push_back(wp);
		thisUI.NormalSprites2.push_back(wp);
		dropDownList.push_back(wp);
		textDropDown.push_back(TextUI());
		textDropDown.rbegin()->SetColor(Color::Transparent);
		textDropDown.rbegin()->SetParent(wp);
		for (auto& wp1 : textDropDown.rbegin()->getSprites()) 
			thisUI.NormalSprites2.push_back(wp1);
		
	}
	{
		thisUI.nextRoomButton = Instantiate<NextRoomButton>();
		weak_ptr<NextRoomButton> wp = thisUI.nextRoomButton;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Next"]);
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(transform->wp);
		wp.lock()->transform->SetPosition(Vector2f(0, 45 * 9));
		thisUI.clickableSprites.push_back(wp);
		thisUI.NormalSprites2.push_back(wp);
	}
	{
		thisUI.previouseRoomButton = Instantiate<PreviousRoomButton>();
		weak_ptr<PreviousRoomButton> wp = thisUI.previouseRoomButton;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Previous"]);
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(transform->wp);
		wp.lock()->transform->SetPosition(Vector2f(0, 45 * 10));
		thisUI.clickableSprites.push_back(wp);
		thisUI.NormalSprites2.push_back(wp);
	}
	UpdateText();
}
void RoomDropDownButton::GotoNextPage()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	if ((dropDownPage+1) * 8< WControl::allRoomPrefabs()[thisUI.choosingSet].second.size()) {
		dropDownPage++;
		thisUI.ChangeRoom(dropDownPage*8);
	}
}
void RoomDropDownButton::GotoPreviousPage()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	if (dropDownPage > 0) {
		dropDownPage--;
		thisUI.ChangeRoom(dropDownPage * 8);
	}
}
void RoomDropDownButton::Open()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	for (auto wp : dropDownList) {
		wp.lock()->transform->renderBox.setFillColor(Color::White);
	}
	for (auto texts : textDropDown) {
		texts.SetColor(Color::White);
	}
	{
		thisUI.nextRoomButton.lock()->transform->renderBox.setFillColor(Color::White);
		thisUI.previouseRoomButton.lock()->transform->renderBox.setFillColor(Color::White);
	}
	{
		thisUI.newRoomButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.editButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.deleteRoomButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.deleteSetButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
	}
	isOpen = true;
}
void RoomDropDownButton::Close()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	for (auto wp : dropDownList) {
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
	}
	for (auto& texts : textDropDown) {
		texts.SetColor(Color::Transparent);
	}
	{
		thisUI.nextRoomButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.previouseRoomButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
	}
	{
		thisUI.newRoomButton.lock()->transform->renderBox.setFillColor(Color::White);
		thisUI.editButton.lock()->transform->renderBox.setFillColor(Color::White);
		thisUI.deleteRoomButton.lock()->transform->renderBox.setFillColor(Color::White);
		thisUI.deleteSetButton.lock()->transform->renderBox.setFillColor(Color::White);
	}
	isOpen = false;
}
void RoomDropDownButton::UpdateText()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	int j = 0;
	if (thisUI.choosingRoomIndex < WControl::allRoomPrefabs()[thisUI.choosingSet].second.size()) {
		choosedText.SetText(WControl::allRoomPrefabs()[thisUI.choosingSet].second[thisUI.choosingRoomIndex].name);
		int i = 0;
		for (; i + dropDownPage * 8< WControl::allRoomPrefabs()[thisUI.choosingSet].second.size();i++) {
			auto& room= WControl::allRoomPrefabs()[thisUI.choosingSet].second[i + dropDownPage * 8];
			if (i < 8) {
				dropDownList[i].lock()->index = i+ dropDownPage * 8;
				int j = 0;
				textDropDown[i].SetText(room.name);
			}
		}
		for (; i < 8; i++) {
			dropDownList[i].lock()->name = "";
			textDropDown[i].SetText("");
		}
	}
	else {
		choosedText.SetText("");
		for (int i = 0; i < 8; i++) {
			textDropDown[i].SetText("");
		}
	}
	
}
void RoomDropDownButton::Activate()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	if (!thisUI.dropDown1.lock()->isOpen) {
		if (!isOpen)
			Open();
		else
			Close();
	}
}

void RoomDropDownButton::SetAllVisible(const bool b)
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

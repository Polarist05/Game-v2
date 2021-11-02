#include "SetDropDownButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"
#include <iostream>
void SetDropDownButton::InstantList()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	for (int i = 0; i < 10; i++) {
		weak_ptr<GameSprite> wp = Instantiate<GameSprite>();
		choosedText.push_back(wp);
		wp.lock()->transform->renderBox.setFillColor(Color::White);
		wp.lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
		wp.lock()->transform->SetAllSpriteOffset(WControl::TextOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(transform->wp);
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
		textDropDown.push_back(vector<weak_ptr<GameSprite>>());
		for (int j = 0; j < 10; j++) {
			weak_ptr<GameSprite> wp1 = Instantiate<GameSprite>();
			wp1.lock()->transform->renderBox.setFillColor(Color::Transparent);
			wp1.lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
			wp1.lock()->transform->SetAllSpriteOffset(WControl::TextOffsetData());
			wp1.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp1.lock()->transform->SetParent(wp);
			wp1.lock()->transform->SetPosition(Vector2f(-wp.lock()->transform->renderBox.getSize().x / 2 + wp1.lock()->transform->renderBox.getSize().x * (j + 1.5), 0));
			thisUI.NormalSprites2.push_back(wp1);
			textDropDown[i].push_back(wp1);
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
	for (auto texts : textDropDown) {
		for (auto wp1 : texts) {
			wp1.lock()->transform->renderBox.setFillColor(Color::White);
		}
	}
	for (auto wp : thisUI.dropDown2.lock()->choosedText) {
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
	}
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
		for (auto wp1 : texts) {
			wp1.lock()->transform->renderBox.setFillColor(Color::Transparent);
		}
	}
	for (auto wp : thisUI.dropDown2.lock()->choosedText) {
		wp.lock()->transform->renderBox.setFillColor(Color::White);
	}
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
	int	i = 0;
	ToolkitUI& thisUI = *(ToolkitUI*)WControl::AllUI()[UIType::ToolkitPage];

	int j = 0;
	for (; j < thisUI.choosingSet.size() && j < 10; j++) {
		if (thisUI.choosingSet[j] >= 'a' && thisUI.choosingSet[j] <= 'z') {
			choosedText[j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[thisUI.choosingSet[j] - 'a' + 'A']);
		}
		else
			choosedText[j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[thisUI.choosingSet[j]]);
	}
	for (; j < 10; j++) {
		choosedText[j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
	}
	for (auto& roomSet : WControl::allRoomPrefabs()) {
		if (i < 10) {
			dropDownList[i].lock()->name = roomSet.first;
			int j = 0;
			for (; j < roomSet.first.size() && j < 10; j++) {
				if (roomSet.first[j] >= 'a' && roomSet.first[j] <= 'z') {
					textDropDown[i][j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[roomSet.first[j] - 'a' + 'A']);
				}
				else
					textDropDown[i][j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[roomSet.first[j]]);
			}
			for (; j < 10; j++) {
				textDropDown[i][j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
			}
			std::cout << "Room " << (char)(i + '0') << ": " << roomSet.first << endl;
		}
		i++;
	}
	printf("\n");
	for (; i < 10; i++) {
		dropDownList[i].lock()->name = "";
		for (int j = 0; j < 10; j++) {
			textDropDown[i][j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
		}
	}
	cout << endl;
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
			for(auto& wp:a)
				wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		}
		for (auto& a :choosedText) {
			a.lock()->transform->renderBox.setFillColor(Color::Transparent);
		}
	}
	else {
		transform->renderBox.setFillColor(Color::White);
		for (auto& a : choosedText) {
			a.lock()->transform->renderBox.setFillColor(Color::White);
		}
	}
}

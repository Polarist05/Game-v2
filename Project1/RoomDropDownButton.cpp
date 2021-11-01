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
	for (int i = 0; i < 8; i++) {
		weak_ptr<RoomDropDownList> wp = Instantiate<RoomDropDownList>();
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
	{
		thisUI.nextRoomButton = Instantiate<NextRoomButton>();
		weak_ptr<NextRoomButton> wp = thisUI.nextRoomButton;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Next"]);
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(transform->wp);
		wp.lock()->transform->SetPosition(Vector2f(0, 45 * 9));
		thisUI.clickableTextureSprites.push_back(wp);
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
		thisUI.clickableTextureSprites.push_back(wp);
		thisUI.NormalSprites2.push_back(wp);
	}
	UpdateText();
}
void RoomDropDownButton::GotoNextPage()
{
	ToolkitUI& thisUI = *(ToolkitUI*)WControl::AllUI()[UIType::ToolkitPage];
	if ((dropDownPage+1) * 8< WControl::allRoomPrefabs()[thisUI.choosingSet].second.size()) {
		dropDownPage++;
		thisUI.ChangeRoom(dropDownPage*8);
	}
}
void RoomDropDownButton::GotoPreviousPage()
{
	ToolkitUI& thisUI = *(ToolkitUI*)WControl::AllUI()[UIType::ToolkitPage];
	if (dropDownPage > 0) {
		dropDownPage--;
		thisUI.ChangeRoom(dropDownPage * 8);
	}
}
void RoomDropDownButton::Open()
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
	ToolkitUI& thisUI = *(ToolkitUI*)WControl::AllUI()[UIType::ToolkitPage];
	for (auto wp : dropDownList) {
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
	}
	for (auto texts : textDropDown) {
		for (auto wp1 : texts) {
			wp1.lock()->transform->renderBox.setFillColor(Color::Transparent);
		}
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
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	int j = 0;
	if (thisUI.choosingRoomIndex < WControl::allRoomPrefabs()[thisUI.choosingSet].second.size()) {
		for (; j < WControl::allRoomPrefabs()[thisUI.choosingSet].second[thisUI.choosingRoomIndex].name.size() && j < 10; j++) {
			std::string name = WControl::allRoomPrefabs()[thisUI.choosingSet].second[thisUI.choosingRoomIndex].name;
			if (name[j] >= 'a' && name[j] <= 'z') {
				choosedText[j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[name[j] - 'a' + 'A']);
			}
			else
				choosedText[j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[name[j]]);
		}
		for (; j < 10; j++) {
			choosedText[j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
		}
		int i = 0;
		for (; i + dropDownPage * 8< WControl::allRoomPrefabs()[thisUI.choosingSet].second.size();i++) {
			auto& room= WControl::allRoomPrefabs()[thisUI.choosingSet].second[i + dropDownPage * 8];
			if (i < 8) {
				dropDownList[i].lock()->index = i+ dropDownPage * 8;
				int j = 0;
				for (; j < room.name.size() && j < 10; j++) {
					if (room.name[j] >= 'a' && room.name[j] <= 'z') {
						textDropDown[i][j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[room.name[j] - 'a' + 'A']);
					}
					else
						textDropDown[i][j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[room.name[j]]);
				}
				for (; j < 10; j++) {
					textDropDown[i][j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
				}
			}
		}
		for (; i < 8; i++) {
			dropDownList[i].lock()->name = "";
			for (int j = 0; j < 10; j++) {
				textDropDown[i][j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
			}
		}
		cout << endl;
	}
	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 10; j++) {
				textDropDown[i][j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
			}
			choosedText[i].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
		}
	}
	
}
void RoomDropDownButton::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)WControl::AllUI()[UIType::ToolkitPage];
	if (!thisUI.dropDown1.lock()->isOpen) {
		if (!isOpen)
			Open();
		else
			Close();
	}
}

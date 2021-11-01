#include "ToolkitUI.h"
#include "WorldControl.h"
void ToolkitUI::setText(vector<weak_ptr<GameSprite>>& textSprites, const std::string& s) {
	int mn = min(textSprites.size(), s.size());
	int i = 0;
	for (; i < mn; i++) {
		if (s[i] >= 'a' && s[i] <= 'z')
			textSprites[i].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[s[i] - 'a' + 'A']);
		else
			textSprites[i].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[s[i]]);
	}
	for (;i<textSprites.size();i++) {
		textSprites[i].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
	}
}

void ToolkitUI::ChangeSet(std::string setName)
{
	if (setName != "") {
		ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
		thisUI.choosingSet = setName;
		thisUI.dropDown2.lock()->dropDownPage = 0;
		ChangeRoom(0);
	}
}

void ToolkitUI::ChangeRoom(int index)
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	if (index < WControl::allRoomPrefabs()[thisUI.choosingSet].second.size()) {
		thisUI.choosingRoomIndex = index;
		WControl::GetCurrentRoom().lock()->ResetRoom();
		WControl::GetCurrentRoom().lock()->SetRoomSeed(WControl::allRoomPrefabs()[thisUI.choosingSet].second[thisUI.choosingRoomIndex], false, false);
	}
	else if(!WControl::allRoomPrefabs()[thisUI.choosingSet].second.size()){
		thisUI.choosingRoomIndex = 0;
		WControl::GetCurrentRoom().lock()->ResetRoom();
		WControl::GetCurrentRoom().lock()->SetRoomSeed(RoomData(), false, false);
		thisUI.updateText();
	}
	thisUI.updateText();
}

void ToolkitUI::updateText()
{
	dropDown1.lock()->UpdateText();
	dropDown2.lock()->UpdateText();
}

#include "DeleteRoomButton.h"
#include "ToolkitUI.h"
#include "WorldControl.h"
#include <fstream>
#include <filesystem>
#include <iostream>
void DeleteRoomButton::Activate()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	if (WorldControl::allRoomPrefabs()[thisUI.choosingSet].second.size() > 0&&!WorldControl::allRoomPrefabs()[thisUI.choosingSet].first.second) {
		WorldControl::allRoomPrefabs()[thisUI.choosingSet].second.erase(WorldControl::allRoomPrefabs()[thisUI.choosingSet].second.begin() + thisUI.choosingRoomIndex);
		Load::RefreshRoomPrefrab();
		std::string path = "Rooms\\" + thisUI.choosingSet + "\\";
		std::filesystem::remove(path + to_string(thisUI.choosingRoomIndex));
		for (size_t i = thisUI.choosingRoomIndex; i < WorldControl::allRoomPrefabs()[thisUI.choosingSet].second.size(); i++)
		{
			std::filesystem::rename(path + to_string(i + 1), path + to_string(i));
		}
		if (thisUI.choosingRoomIndex) {
			thisUI.choosingRoomIndex--;
			WControl::GetCurrentRoom().lock()->ResetRoom();
			WControl::GetCurrentRoom().lock()->SetRoomSeed(WControl::allRoomPrefabs()[thisUI.choosingSet].second[thisUI.choosingRoomIndex], false, false);
		}
		if (thisUI.dropDown2.lock()->dropDownPage * 8 >= WorldControl::allRoomPrefabs()[thisUI.choosingSet].second.size()) {
			thisUI.dropDown2.lock()->GotoPreviousPage();
		}
		thisUI.ChangeRoom(thisUI.dropDown2.lock()->dropDownPage*8);
		thisUI.updateText();
	}
}

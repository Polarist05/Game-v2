#include "CreateNewRoomButton.h"
#include "ToolkitUI.h"
#include "WorldControl.h"
#include <fstream>
#include <filesystem>

void CreateNewRoomButton::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	RoomData roomData("newRoom");
	WorldControl::allRoomPrefabs()[thisUI.choosingSet].second.push_back(roomData);
	WControl::RefreshRoomPrefrab();
	thisUI.choosingRoomIndex = WorldControl::allRoomPrefabs()[thisUI.choosingSet].second.size() - 1;
	std::ofstream rooomSave("Rooms\\" + thisUI.choosingSet + '\\' + to_string(thisUI.choosingRoomIndex));
	rooomSave << roomData.name << " " << roomData.roomType << endl;
	for (int j = 0; j < RSIZEY; j++) {
		for (int k = 0; k < RSIZEX; k++) {
			rooomSave << roomData.floor[j][k] << " ";
		}
		rooomSave << endl;
	}
	rooomSave << endl;
	for (int j = 0; j < RSIZEY; j++) {
		for (int k = 0; k < RSIZEX; k++) {
			rooomSave << roomData.objects[j][k] << " ";
		}
		rooomSave << endl;
	}
	rooomSave << endl;
	for (int j = 0; j < RSIZEY; j++) {
		for (int k = 0; k < RSIZEX; k++) {
			rooomSave << roomData.track[j][k] << " ";
		}
		rooomSave << endl;
	}
	rooomSave.close();
	thisUI.updateText();
	WControl::GetCurrentRoom().lock()->ResetRoom();
	WControl::GetCurrentRoom().lock()->SetRoomSeed(WControl::allRoomPrefabs()[thisUI.choosingSet].second[thisUI.choosingRoomIndex], false, false);
}

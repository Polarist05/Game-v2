#include "CreateNewRoomButton.h"
#include "ToolkitUI.h"
#include "WorldControl.h"
#include <fstream>
#include <filesystem>

void CreateNewRoomButton::Activate()
{
	ToolkitUI& toolkitUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	RoomData roomData("newRoom");
	WorldControl::allRoomPrefabs()[toolkitUI.choosingSet].second.push_back(roomData);
	WControl::RefreshRoomPrefrab();
	std::ofstream rooomSave("Rooms\\" + toolkitUI.choosingSet + '\\' + to_string(WorldControl::allRoomPrefabs()[toolkitUI.choosingSet].second.size()-1));
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
}

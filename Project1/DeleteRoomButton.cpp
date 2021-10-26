#include "DeleteRoomButton.h"
#include "ToolkitUI.h"
#include "WorldControl.h"
#include <fstream>
#include <filesystem>
#include <iostream>
void DeleteRoomButton::Activate()
{
	ToolkitUI& toolkitUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	WorldControl::allRoomPrefabs()[toolkitUI.choosingSet].second.erase(WorldControl::allRoomPrefabs()[toolkitUI.choosingSet].second.begin()+ toolkitUI.choosingRoomIndex);
	WControl::RefreshRoomPrefrab();
	std::string path = "Rooms\\" + toolkitUI.choosingSet + "\\";
	std::filesystem::remove(path + to_string(toolkitUI.choosingRoomIndex));
	for (size_t i = toolkitUI.choosingRoomIndex; i < WorldControl::allRoomPrefabs()[toolkitUI.choosingSet].second.size(); i++)
	{
		std::filesystem::rename(path + to_string(i+1), path + to_string(i) );
	}
}

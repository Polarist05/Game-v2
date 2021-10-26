#include "DeleteSetButton.h"
#include "ToolkitUI.h"
#include "WorldControl.h"
#include <fstream>
#include <filesystem>

void DeleteSetButton::Activate()
{
	ToolkitUI& toolkitUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	WControl::allRoomPrefabs().erase(toolkitUI.choosingSet);
	WControl::RefreshRoomPrefrab();
	std::filesystem::remove_all("Rooms\\" + toolkitUI.choosingSet);
}

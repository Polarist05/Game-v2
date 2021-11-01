#include "DeleteSetButton.h"
#include "ToolkitUI.h"
#include "WorldControl.h"
#include <fstream>
#include <filesystem>

void DeleteSetButton::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	if (WControl::allRoomPrefabs().size() > 1) {
		WControl::allRoomPrefabs().erase(thisUI.choosingSet);
		WControl::RefreshRoomPrefrab();
		std::filesystem::remove_all("Rooms\\" + thisUI.choosingSet);
		thisUI.ChangeSet(WControl::allRoomPrefabs().begin()->first);
		thisUI.updateText();
	}
}

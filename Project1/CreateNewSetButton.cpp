#include "CreateNewSetButton.h"
#include "ToolkitUI.h"
#include "WorldControl.h"
#include <fstream>
#include <filesystem>

void CreateNewSetButton::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	{
		int i = 1;
		for (; 1; i++) {
			if (WorldControl::allRoomPrefabs().find("NewSet" + to_string(i)) == WorldControl::allRoomPrefabs().end()) {
				WorldControl::allRoomPrefabs()["NewSet" + to_string(i)];
				break;
			}
		}
		WControl::RefreshRoomPrefrab();
		std::filesystem::create_directory("Rooms\\NewSet" + to_string(i));
		thisUI.ChangeSet("NewSet" + to_string(i));
	}
	thisUI.updateText();
}

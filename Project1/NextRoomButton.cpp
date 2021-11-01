#include "NextRoomButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"

void NextRoomButton::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	thisUI.dropDown2.lock()->GotoNextPage();
}

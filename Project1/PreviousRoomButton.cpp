#include "PreviousRoomButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"

void PreviousRoomButton::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	thisUI.dropDown2.lock()->GotoPreviousPage();
}

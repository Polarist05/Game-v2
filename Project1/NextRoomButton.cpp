#include "NextRoomButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"

void NextRoomButton::Activate()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	thisUI.dropDown2.lock()->GotoNextPage();
}

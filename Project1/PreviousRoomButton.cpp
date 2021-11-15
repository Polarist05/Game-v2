#include "PreviousRoomButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"

void PreviousRoomButton::Activate()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	thisUI.dropDown2.lock()->GotoPreviousPage();
}

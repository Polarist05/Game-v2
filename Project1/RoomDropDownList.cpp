#include "RoomDropDownList.h"
#include "WorldControl.h"
#include "ToolkitUI.h"

void RoomDropDownList::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	thisUI.dropDown2.lock()->isOpen = false;
	thisUI.ChangeRoom(index);
	dynamic_pointer_cast<RoomDropDownButton>(transform->parent.lock())->Close();
}

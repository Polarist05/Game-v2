#include "SetDropDownListButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"

void SetDropDownListButton::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	thisUI.dropDown2.lock()->isOpen = false;
	thisUI.ChangeSet(name);
	dynamic_pointer_cast<SetDropDownButton>(transform->parent.lock())->Close();
}
#include "SaveButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"
void SaveButton::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
}

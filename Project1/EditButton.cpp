#include "EditButton.h"
#include "ToolkitUI.h"
#include "WorldControl.h"
void EditButton::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
}

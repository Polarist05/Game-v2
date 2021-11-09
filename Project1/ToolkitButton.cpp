#include "ToolkitButton.h"
#include "WorldControl.h"
void ToolkitButton::Activate()
{
	WControl::getMainDungeon().GenerateToolkitMode();
	currentMode() = toolkitMode();
	WControl::UIStack().push(UIType::ToolkitPage);
	printf("Toolkit\n");
}

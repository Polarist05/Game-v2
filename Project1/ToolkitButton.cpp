#include "ToolkitButton.h"
#include "WorldControl.h"
void ToolkitButton::Activate()
{
	WControl::getMainDungeon().ResetDungeon();
	WControl::getMainDungeon().GenerateToolkitMode();
	Mode::currentMode() = Mode::toolkitMode();
	WControl::UIStack().push(UIType::ToolkitPage);
	printf("Toolkit\n");
}

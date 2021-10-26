#include "ToolkitButton.h"
#include "WorldControl.h"
void ToolkitButton::Activate()
{
	WControl::getMainDungeon().GenerateToolkitMode();
	WControl::isGamePlaying() = true;
	WControl::UIStack().push(UIType::ToolkitPage);
	printf("Toolkit\n");
}

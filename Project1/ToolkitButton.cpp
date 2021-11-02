#include "ToolkitButton.h"
#include "WorldControl.h"
void ToolkitButton::Activate()
{
	WControl::getMainDungeon().GenerateToolkitMode();
	WControl::getGameMode() = GameMode::ToolkitEditMode;
	WControl::UIStack().push(UIType::ToolkitPage);
	printf("Toolkit\n");
}

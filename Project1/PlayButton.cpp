#include "PlayButton.h"
#include "WorldControl.h"
void PlayButton::Activate()
{
	currentMode() = playMode();
	currentMode().lock()->SetUp();
	WControl::UIStack().pop();
}

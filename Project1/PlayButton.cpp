#include "PlayButton.h"
#include "WorldControl.h"
void PlayButton::Activate()
{
	WControl::getMainDungeon().ResetDungeon();
	Mode::currentMode() = Mode::playMode();
	Mode::currentMode().lock()->SetUp();
	WControl::UIStack().pop();
}

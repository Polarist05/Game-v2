#include "PlayButton.h"
#include "WorldControl.h"
void PlayButton::Activate()
{
	WControl::player().lock()->ResetKey();
	WControl::player().lock()->ResetSoul();
	WControl::getMainDungeon().ResetDungeon();
	WControl::player().lock()->ResetScore();
	Mode::currentMode() = Mode::playMode();
	Mode::currentMode().lock()->SetUp();
	WControl::UIStack().pop();
}

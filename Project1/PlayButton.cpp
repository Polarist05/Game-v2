#include "PlayButton.h"
#include "WorldControl.h"
void PlayButton::Activate()
{
	WControl::getMainDungeon().GenerateDungeon();
	WControl::getGameMode() = GameMode::PlayMode;
	WControl::UIStack().pop();
	printf("Play\n");
}

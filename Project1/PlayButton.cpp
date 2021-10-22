#include "PlayButton.h"
#include "WorldControl.h"
void PlayButton::Activate()
{
	WControl::getMainDungeon().GenerateDungeon();
	WControl::isGamePlaying() = true;
	WControl::UIStack().pop();
	printf("Play\n");
}

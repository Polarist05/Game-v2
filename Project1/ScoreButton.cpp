#include "ScoreButton.h"
#include "WorldControl.h"
void ScoreButton::Activate()
{
	WControl::getMainDungeon().ResetDungeon();
	WControl::isGamePlaying() = false;
	printf("Score\n");
}

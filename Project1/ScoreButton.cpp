#include "ScoreButton.h"
#include "WorldControl.h"
void ScoreButton::Activate()
{
	WControl::getMainDungeon().ResetDungeon();
	printf("Score\n");
}

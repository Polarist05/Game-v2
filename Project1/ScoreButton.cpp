#include "ScoreButton.h"
#include "WorldControl.h"
void ScoreButton::Activate()
{
	Mode::currentMode() = Mode::endGameMode();
	Mode::currentMode().lock()->SetUp();
	printf("Score\n");
}

#include "PlayMode.h"
#include "WorldControl.h"
#include "Update.h"
void PlayMode::Start()
{
	
}

void PlayMode::SetUp()
{
	WControl::getMainDungeon().GenerateDungeon();
	runTime = 0;
	lastFrameTime = clock();
}

void PlayMode::Update()
{
	runTime += clock() - lastFrameTime;
	lastFrameTime = clock();
	Update::UpdatePlayer();
	Update::UpdateUX();
	Update::UpdateKnife();
	Update::UpdateObject();
	Update::UpdateRoom();
}

void PlayMode::CheckKeyPress()
{
	KeyPress::CheckPlayerMovement();
	KeyPress::CheckPlayerAction();
	KeyPress::CheckEscape();
}

void PlayMode::RenderGame()
{
	GameRenderer::RenderWallAndFloor();
	GameRenderer::RenderPlayerAndObject();
	GameRenderer::RenderKnife();
	GameRenderer::RenderUX();
}

time_t PlayMode::getRunTime()
{
	return runTime;
}

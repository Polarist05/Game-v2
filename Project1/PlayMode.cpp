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
	UpdatePlayer();
	UpdateUX();
	UpdateKnife();
	UpdateObject();
	UpdateRoom();
}

void PlayMode::CheckKeyPress()
{
	CheckPlayerMovement();
	CheckPlayerAction();
	CheckEscape();
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

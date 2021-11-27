#include "PlayMode.h"
#include "WorldControl.h"
#include "Update.h"
void PlayMode::Start()
{
	
}

void PlayMode::SetUp()
{
	WControl::music().setPlayingOffset(Time());
	WControl::music().play();
	WControl::getMainDungeon().GenerateDungeon();
	WControl::player().lock()->SetPlayerDirection(Direction::Down);
	WControl::player().lock()->playerState = e_Stop;
	WControl::GetCurrentRoom().lock()->startRoomPosition= WControl::GetCurrentRoom().lock()->GetTransform()->GetRealPositionAt(Vector2i(4,3));
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
	Update::UpdateFireFlies();
}

void PlayMode::CheckKeyPress()
{
	if (Keyboard::isKeyPressed(Keyboard::T)) {
		WControl::GetCurrentRoom().lock()->RestartRoom();
	}
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
	GameRenderer::Renderfireflies();
}

time_t PlayMode::getRunTime()
{
	return runTime;
}

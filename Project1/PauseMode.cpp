#include "PauseMode.h"
#include "Update.h"
void PauseMode::Start()
{

}

void PauseMode::Update()
{
	Update::UpdateUX();
	Update::UpdateUI();
}

void PauseMode::CheckKeyPress()
{
	KeyPress::CheckClickableSprite();
}

void PauseMode::RenderGame()
{
	GameRenderer::RenderUI();
}
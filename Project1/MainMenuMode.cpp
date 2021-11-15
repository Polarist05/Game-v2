#include "MainMenuMode.h"
#include "Update.h"
void MainMenuMode::Start()
{

}

void MainMenuMode::Update()
{
	Update::UpdateUX();
	Update::UpdateUI();
}

void MainMenuMode::CheckKeyPress()
{
	KeyPress::CheckClickableSprite();
}

void MainMenuMode::RenderGame()
{
	GameRenderer::RenderUI();
}

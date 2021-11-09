#include "MainMenuMode.h"
#include "Update.h"
void MainMenuMode::Start()
{

}

void MainMenuMode::Update()
{
	UpdateUX();
	UpdateUI();
}

void MainMenuMode::CheckKeyPress()
{
	CheckClickableSprite();
}

void MainMenuMode::RenderGame()
{
	GameRenderer::RenderUI();
}

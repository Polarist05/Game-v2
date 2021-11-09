#include "ToolkitMode.h"
#include "WorldControl.h"
#include "Update.h"
void ToolkitMode::Start()
{
}

void ToolkitMode::Update()
{
	UpdateUI();
}

void ToolkitMode::CheckKeyPress()
{
	CheckEscape();
	CheckClickableSprite();
	CheckEditArea();
}

void ToolkitMode::RenderGame()
{
	std:cout << "In Render of toolkit" << endl;
	GameRenderer::RenderWallAndFloor();
	GameRenderer::RenderPlayerAndObject();
	GameRenderer::RenderAreaHilight();
	GameRenderer::RenderUI();
}

#include "ToolkitMode.h"
#include "WorldControl.h"
#include "Update.h"
void ToolkitMode::Start()
{

}

void ToolkitMode::Update()
{
	Update::UpdateUI();
}

void ToolkitMode::CheckKeyPress()
{
	KeyPress::CheckEscape();
	KeyPress::CheckClickableSprite();
	KeyPress::CheckEditArea();
}

void ToolkitMode::RenderGame()
{
	GameRenderer::RenderWallAndFloor();
	GameRenderer::RenderPlayerAndObject();
	GameRenderer::RenderAreaHilight();
	GameRenderer::RenderUI();
}

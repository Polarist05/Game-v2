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
	if (ALLUI::toolkitUI().saveButton.lock()->transform->renderBox.getFillColor()!=Color::Transparent&&Mouse::isButtonPressed(Mouse::Right)) {
		Vector2i areaPosition = WControl::GetCurrentRoom().lock()->GetTransform()->GetPositionInTileAt(WControl::GetCursurPosition());
		weak_ptr<Input> in = dynamic_pointer_cast<Input>(WControl::GetCurrentRoom().lock()->Space[areaPosition.y-1][areaPosition.x-1].lock());
		weak_ptr<Output> out = dynamic_pointer_cast<Output>(WControl::GetCurrentRoom().lock()->Space[areaPosition.y-1][areaPosition.x-1].lock());
		weak_ptr<PortalClass> portal = dynamic_pointer_cast<PortalClass>(WControl::GetCurrentRoom().lock()->Space[areaPosition.y-1][areaPosition.x-1].lock());
		if (!in.expired()||!out.expired()||!portal.expired() ) 
		{
			cout << "Enter group index you want" << endl;
			char c;
			while (1) {
				sleep(sf::milliseconds(100) );
				c = KeyPress::CheckAlphaBetOrNumberKey();
				if (c >= '0' && c <= '9') {
					ALLUI::toolkitUI().newRoomData.objects[areaPosition.y - 1][areaPosition.x - 1] = (ALLUI::toolkitUI().newRoomData.objects[areaPosition.y - 1][areaPosition.x - 1] / 10) * 10 + c - '0';
					cout << "Change index complete" << endl;
					break;
				}
				if (Keyboard::isKeyPressed(Keyboard::BackSpace))
					break;
			}
			
			
		}
	}
}

void ToolkitMode::RenderGame()
{
	GameRenderer::RenderWallAndFloor();
	GameRenderer::RenderPlayerAndObject();
	GameRenderer::RenderAreaHilight();
	GameRenderer::RenderUI();
}

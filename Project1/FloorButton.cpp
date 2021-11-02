#include "FloorButton.h"
#include "WorldControl.h"
FloorButton::FloorButton():ClickableSprite(){}
FloorButton::FloorButton(std::string s):ClickableSprite(s){}

void FloorButton::Activate()
{
	for (auto& x : WControl::GetChosedAreaPosition()) {
		for (auto& y : x.second) {
			if((x.first+y)%2)
				WControl::GetCurrentRoom().lock()->areas[y - 1][x.first - 1].lock()->GetTransform()->renderBox.setFillColor(Color::Magenta);
			else
				WControl::GetCurrentRoom().lock()->areas[y - 1][x.first - 1].lock()->GetTransform()->renderBox.setFillColor(Color::Black);
		}
	}
}

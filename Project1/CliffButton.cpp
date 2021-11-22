#include "CliffButton.h"
#include "WorldControl.h"
CliffButton::CliffButton():ClickableSprite(){}

CliffButton::CliffButton(std::string s):ClickableSprite(s){}

void CliffButton::Activate()
{
	for (auto& x : WControl::GetChosedAreaPosition()) {
		for (auto& y : x.second) {
			WControl::GetCurrentRoom().lock()->areas[y - 1][x.first - 1].lock()->GetTransform()->renderBox.setFillColor(Color::Black);
		}
	}
}

#include "UI.h"

void UI::SetVisible(bool b)
{
	if (b) {
		for (weak_ptr<ClickableSprite> wp : clickableSprites) {
			Color color = wp.lock()->transform->renderBox.getFillColor();
			color.a = 255;
			wp.lock()->transform->renderBox.setFillColor(color);
		}
	}
	else{
		for (weak_ptr<ClickableSprite> wp : clickableSprites) {
			Color color = wp.lock()->transform->renderBox.getFillColor();
			color.a = 0;
			wp.lock()->transform->renderBox.setFillColor(color);
		}
	}
}

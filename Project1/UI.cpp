#include "UI.h"
#include "WorldControl.h"
#include "Collision.h"
void UI::CheckUICollision()
{
	Vector2f cursurPos = WControl::GetCursurPosition();
	if (!WControl::clickableSpriteAtCursor().expired()) {
		if (!Collision::isCollision(WControl::clickableSpriteAtCursor().lock()->transform->hitBox, cursurPos) && !Mouse::isButtonPressed(Mouse::Button::Left)) {
			WControl::clickableSpriteAtCursor().reset();
		}
		else
			return;
	}
	if (!WControl::UIStack().empty()) {
		for (auto wp : ALLUI::GetUI(WControl::UIStack().top())->clickableSprites) {
			if (wp.lock()->transform->renderBox.getFillColor() != Color::Transparent) {
				if (Collision::isCollision(wp.lock()->transform->renderBox, cursurPos)) {
					WControl::clickableSpriteAtCursor() = wp;
					wp.lock()->transform->renderBox.setFillColor(Color::Yellow);
				}
				else {
					wp.lock()->transform->renderBox.setFillColor(Color::White);
				}
			}
		}
	}
}

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

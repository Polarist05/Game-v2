#include "ChoosingEdge.h"

const Color ChoosingEdge::GetColor(){return color;}
void ChoosingEdge::SetColor(const Color& color){
	this->color = color;
	transform->renderBox.setFillColor(color);
}

void ChoosingEdge::Activate()
{
	if (direction == Direction::Up|| direction == Direction::Left) {
		if (transform->renderBox.getFillColor()==Color::Cyan) {
			SetColor(Color::Green);
		}
		if (transform->renderBox.getFillColor() == Color::Green) {
			SetColor(Color(32, 32, 32, 255));
		}
		if (transform->renderBox.getFillColor() == Color(32, 32, 32, 255)) {
			SetColor(Color::Cyan);
		}
	}
}

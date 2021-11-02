#include "ChoosingEdge.h"
#include "WorldControl.h"
void ChoosingEdge::Activate()
{
	if (direction == Direction::Up|| direction == Direction::Left) {
		if (transform->renderBox.getTexture()==&WControl::otherPrefab()["Wall"]) {
			transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		}
		else if (transform->renderBox.getTexture() == &WControl::otherPrefab()["In"]) {
			transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		}
		else if (transform->renderBox.getTexture() == &WControl::otherPrefab()["Out"]) {
			transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		}
	}
	if (direction == Direction::Down || direction == Direction::Right) {
		if (transform->renderBox.getTexture() == &WControl::otherPrefab()["Wall"]) {
			transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		}
		else if (transform->renderBox.getTexture() == &WControl::otherPrefab()["Out"]) {
			transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		}
	}
}

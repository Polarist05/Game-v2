#include "GameSprite.h"
/*void GameTransform::SetAnchorType(AnchorType _anchor) {
	switch (_anchor)
	{
	case TopLeft:
		hitBox.setOrigin(0, 0);
		break;
	case TopCentor:
		hitBox.setOrigin(hitBox.getSize().x / 2, 0);
		break;
	case TopRight:
		hitBox.setOrigin(hitBox.getSize().x, 0);
		break;
	case MiddleLeft:
		hitBox.setOrigin(0, hitBox.getSize().y / 2);
		break;
	case MiddleCentor:
		hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);
		break;
	case MiddleRight:
		hitBox.setOrigin(hitBox.getSize().x, hitBox.getSize().y / 2);
		break;
	case DownLeft:
		hitBox.setOrigin(0, hitBox.getSize().y);
		break;
	case DownCentor:
		hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y);
		break;
	case DownRight:
		hitBox.setOrigin(hitBox.getSize().x, hitBox.getSize().y);
		break;
	}
}

void GameTransform::SetScale(float x, float y) {

	hitBox.setScale(x, y);
	if (fixWidth) { spriteBox.setScale(x, spriteBox.getScale().y * x / scale.x); }
	else { spriteBox.setScale(spriteBox.getScale().x * y / scale.y, y); }
	scale = Vector2f(x, y);
}
void GameTransform::SetPosition(float x, float y) {

}*/
GameTransform::GameTransform(weak_ptr<GameSprite> wp, type_index typeIndex) {
	this->typeIndex = typeIndex;
}
GameTransform::GameTransform() {
	printf("You don't constuct gameSprite by instantiate,Check your code\n");
}
GameTransform::~GameTransform() {
	for (int i = 0; i < childs.size(); i++) {
		Destroy(childs[i].lock()->wp, typeIndex);
	}
}
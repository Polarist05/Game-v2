#include "GameSprite.h"
bool GameTransform::CheckGameTransfromInitialize() {
	if (this->wp.expired()) {
		printf("This wp are expire now.You must initialize before use other command or maybe you already clear this wp");
		return 1;
	}
	else
		return 0;
}
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
GameTransform::GameTransform() {}
void GameTransform::SetParent(weak_ptr<GameSprite> parent){
	shared_ptr<GameSprite> sp = parent.lock();
	if (CheckGameTransfromInitialize())
		return;
	if (sp->transform.CheckGameTransfromInitialize()) {
		printf("Your parent already expire");
		return;
	}
	this->parent = parent;
	if (sp != Hierachy().lock()) 
		this->root = sp->transform.root;
	else 
		this->root = wp;
	sp->transform.childs.push_back(this->wp);
}
GameTransform::GameTransform(weak_ptr<GameSprite> wp, type_index typeIndex) :wp(wp),typeIndex(typeIndex) {
	this->SetParent(Hierachy());
}
GameTransform::~GameTransform() {
	for (int i = 0; i < childs.size(); i++) {
		Destroy(childs[i].lock()->wp(), typeIndex);
	}
}
weak_ptr<GameSprite> GameSprite::wp() {
	return transform.wp;
}
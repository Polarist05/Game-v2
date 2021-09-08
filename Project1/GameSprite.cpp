#include "GameSprite.h"
#include "WorldControl.h"
#include <iostream>
Vector2f GameSprite::GameTransform::DistantFromMiddleCenter(RectangleShape& rect,Vector2f v) {
	return Vector2f(rect.getSize().x/2, rect.getSize().y/2) + v;
}
void GameSprite::GameTransform::SetAnchorType(AnchorType _anchor,BoxType boxType) {
	Vector2f nPos;
	Vector2f* _offsetBox= &OffsetHitBox;
	RectangleShape* _box=&hitBox;
	switch (boxType)
	{
	case BoxType::HitBox:
		_box = &hitBox;
		_offsetBox = &OffsetHitBox;
		break;
	case BoxType::RenderBox:
		_box = &renderBox;
		_offsetBox = &OffsetRenderBox;
		break;
	case BoxType::SpriteBox:
		_box = &spriteBox;
		_offsetBox = &OffsetRenderBox;
		break;
		//Fixlater
	}
	RectangleShape& box = *_box;
	Vector2f& offsetBox = *_offsetBox;
	switch (_anchor)
	{
	case TopLeft:
		nPos=Vector2f(0,0);
		offsetBox = nPos - box.getOrigin();
		box.move(offsetBox.x * box.getScale().x, offsetBox.y * box.getScale().y);
		box.setOrigin(nPos);
		break;
	case TopCentor:
		nPos=Vector2f(box.getSize().x / 2, 0);
		offsetBox = nPos - box.getOrigin();
		box.move(offsetBox.x * box.getScale().x, offsetBox.y * box.getScale().y);
		box.setOrigin(nPos);
		break;
	case TopRight:
		nPos=Vector2f(box.getSize().x, 0);
		offsetBox = nPos - box.getOrigin();
		box.move(offsetBox.x * box.getScale().x, offsetBox.y * box.getScale().y);
		box.setOrigin(nPos);
		break;
	case MiddleLeft:
		nPos=Vector2f(0, box.getSize().y / 2);
		offsetBox = nPos - box.getOrigin();
		box.move(offsetBox.x * box.getScale().x, offsetBox.y * box.getScale().y);
		box.setOrigin(nPos);
		break;
	case MiddleCentor:
		nPos=Vector2f(box.getSize().x / 2, box.getSize().y / 2);
		offsetBox = nPos - box.getOrigin();
		box.move(offsetBox.x * box.getScale().x, offsetBox.y * box.getScale().y);
		box.setOrigin(nPos);
		break;
	case MiddleRight:
		nPos=Vector2f(box.getSize().x, box.getSize().y / 2);
		offsetBox = nPos - box.getOrigin();
		box.move(offsetBox.x * box.getScale().x, offsetBox.y * box.getScale().y);
		box.setOrigin(nPos);
		break;
	case DownLeft:
		nPos=Vector2f(0, box.getSize().y);
		offsetBox = nPos - box.getOrigin();
		box.move(offsetBox.x * box.getScale().x, offsetBox.y * box.getScale().y);
		box.setOrigin(nPos);
		break;
	case DownCentor:
		nPos=Vector2f(box.getSize().x / 2, box.getSize().y);
		offsetBox = nPos - box.getOrigin();
		box.move(offsetBox.x * box.getScale().x, offsetBox.y * box.getScale().y);
		box.setOrigin(nPos);
		break;
	case DownRight:
		nPos=Vector2f(box.getSize().x, box.getSize().y);
		offsetBox = nPos - box.getOrigin();
		box.move(offsetBox.x * box.getScale().x, offsetBox.y * box.getScale().y);
		box.setOrigin(nPos);
		break;
	}
}
/*
void GameTransform::SetScale(float x, float y) {

	hitBox.setScale(x, y);
	if (fixWidth) { spriteBox.setScale(x, spriteBox.getScale().y * x / scale.x); }
	else { spriteBox.setScale(spriteBox.getScale().x * y / scale.y, y); }
	scale = Vector2f(x, y);
}*/
void GameSprite::GameTransform::SetPosition(float x, float y) {
	
}
void GameSprite::GameTransform::SetParent(weak_ptr<GameSprite> parent){
	if (parent.expired()) {
		printf("parent is null please add value\n");
		return;
	}
	if (!this->parent.expired()) {
		this->parent.lock()->transform.childs[childIndex].reset();
	}
	shared_ptr<GameSprite> sp = parent.lock();
	this->parent = parent;
	sp->transform.childs.push_back(this->wp);
	this->childIndex = (int)sp->transform.childs.size()-1;
}
GameSprite::GameTransform::~GameTransform() {}
GameSprite::GameSprite() {}
GameSprite::GameSprite(std::string s) : name(s) { }
GameSprite::~GameSprite() {
	cout << name << " has been destroy" << endl;
	for (int i = 0; i < transform.childs.size(); i++) {
		if (!transform.childs[i].expired()) {
			type_index typeIndex = transform.childs[i].lock()->transform.typeIndex;
			Destroy(transform.childs[i], typeIndex);
		}
	}
}
void GameSprite::SetTransform(weak_ptr<GameSprite> wp, type_index typeIndex) {
	if (wp.expired()) {
		printf("wp is null please add value");
		return;
	}
	transform.wp = wp;
	transform.typeIndex = typeIndex;
	if (!WorldControl::Hierarchy().expired()) {
		transform.SetParent(WorldControl::Hierarchy());
	}
}
void SetGameSprite(weak_ptr<GameSprite> wp, type_index t) {
	if (!wp.expired()) {
		wp.lock()->SetTransform(wp,t);
	}
	else {
		printf("wp in SetGameSprite is null\n");
	}
}
#include "GameSprite.h"
#include "WorldControl.h"
#include <iostream>
Vector2f Multiple(const Vector2f& a, const Vector2f& b);
Vector2f Multiple(const Vector2f& a, const Vector2f& b, const Vector2f& c);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>GameTransfrom<<<<<<<<<<<<<<<<<<<<<<<<
void GameSprite::GameTransform::SetSize(const Vector2f& boxSize,const BoxType& boxType) {
	AnchorType anchorType;
	switch (boxType)
	{
	case RenderBox:
		renderBox.setSize(boxSize);
		anchorType = renderBoxAnchorType;
		break;
	case PseudoRenderBox:
		pseudoRenderBox.setSize(boxSize);
		anchorType = pseudoRenderBoxAnchorType;
		break;
	case HitBox:
		hitBox.setSize(boxSize);
		anchorType = hitBoxAnchorType;
		break;
	}
	SetAnchorType(anchorType, boxType,FIX_ONLY_ANCHOR_POSITION);
}
void GameSprite::GameTransform::SetAnchorType(const AnchorType& _anchor,const BoxType& boxType) {
	Vector2f nPos;
	Vector2f* _offsetBox= &OffsetHitBox;
	RectangleShape* _box=&hitBox;
	AnchorType* _anchorType= &hitBoxAnchorType;
	switch (boxType)
	{
		case BoxType::HitBox:
			_box = &hitBox;
			_offsetBox = &OffsetHitBox;
			_anchorType = &hitBoxAnchorType;
			break;
		case BoxType::RenderBox:
			_box = &renderBox;
			_offsetBox = &OffsetRenderBox;
			_anchorType = &renderBoxAnchorType;
			break;
		case BoxType::PseudoRenderBox :
			_box = &pseudoRenderBox;
			_offsetBox = &OffsetPseudoRenderBox;
			_anchorType = &pseudoRenderBoxAnchorType;
			break;
	}
	RectangleShape& box = *_box;
	Vector2f& offsetBox = *_offsetBox;
	AnchorType& anchorType = *_anchorType;
	switch (_anchor)
	{
	case TopLeft:
		nPos=Vector2f(0,0);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		anchorType = TopLeft;
		break;
	case TopCentor:
		nPos=Vector2f(box.getSize().x / 2, 0);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		anchorType = TopCentor;
		break;
	case TopRight:
		nPos=Vector2f(box.getSize().x, 0);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		anchorType = TopRight;
		break;
	case MiddleLeft:
		nPos=Vector2f(0, box.getSize().y / 2);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		anchorType = MiddleLeft;
		break;
	case MiddleCentor:
		nPos=Vector2f(box.getSize().x / 2, box.getSize().y / 2);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		anchorType = MiddleCentor;
		break;
	case MiddleRight:
		nPos=Vector2f(box.getSize().x, box.getSize().y / 2);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		anchorType = MiddleRight;
		break;
	case DownLeft:
		nPos=Vector2f(0, box.getSize().y);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		anchorType = DownLeft;
		break;
	case DownCentor:
		nPos=Vector2f(box.getSize().x / 2, box.getSize().y);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		anchorType = DownCentor;
		break;
	case DownRight:
		nPos=Vector2f(box.getSize().x, box.getSize().y);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		anchorType = DownRight;
		break;
	}
}
void GameSprite::GameTransform::SetAnchorType(AnchorType _anchor, BoxType boxType,bool FIXTYPE) {
	if (FIXTYPE == FIX_ALL_RECT_POSITION) {
		SetAnchorType(_anchor, boxType);
		return;
	}
	Vector2f nPos;
	Vector2f* _offsetBox = &OffsetHitBox;
	RectangleShape* _box = &hitBox;
	AnchorType* _anchorType = &hitBoxAnchorType;
	switch (boxType)
	{
	case BoxType::HitBox:
		_box = &hitBox;
		_offsetBox = &OffsetHitBox;
		_anchorType = &hitBoxAnchorType;
		break;
	case BoxType::RenderBox:
		_box = &renderBox;
		_offsetBox = &OffsetRenderBox;
		_anchorType = &renderBoxAnchorType;
		break;
	case BoxType::PseudoRenderBox:
		_box = &pseudoRenderBox;
		_offsetBox = &OffsetPseudoRenderBox;
		_anchorType = &pseudoRenderBoxAnchorType;
		break;
	}
	RectangleShape& box = *_box;
	Vector2f& offsetBox = *_offsetBox;
	AnchorType& anchorType = *_anchorType;
	switch (_anchor)
	{
	case TopLeft:
		nPos = Vector2f(0, 0);
		box.setOrigin(nPos);
		anchorType = TopLeft;
		break;
	case TopCentor:
		nPos = Vector2f(box.getSize().x / 2, 0);
		box.setOrigin(nPos);
		anchorType = TopCentor;
		break;
	case TopRight:
		nPos = Vector2f(box.getSize().x, 0);
		box.setOrigin(nPos);
		anchorType = TopRight;
		break;
	case MiddleLeft:
		nPos = Vector2f(0, box.getSize().y / 2);
		box.setOrigin(nPos);
		anchorType = MiddleLeft;
		break;
	case MiddleCentor:
		nPos = Vector2f(box.getSize().x / 2, box.getSize().y / 2);
		box.setOrigin(nPos);
		anchorType = MiddleCentor;
		break;
	case MiddleRight:
		nPos = Vector2f(box.getSize().x, box.getSize().y / 2);
		box.setOrigin(nPos);
		anchorType = MiddleRight;
		break;
	case DownLeft:
		nPos = Vector2f(0, box.getSize().y);
		box.setOrigin(nPos);
		anchorType = DownLeft;
		break;
	case DownCentor:
		nPos = Vector2f(box.getSize().x / 2, box.getSize().y);
		box.setOrigin(nPos);
		anchorType = DownCentor;
		break;
	case DownRight:
		nPos = Vector2f(box.getSize().x, box.getSize().y);
		box.setOrigin(nPos);
		anchorType = DownRight;
		break;
	}
}
void GameSprite::GameTransform::Move(Vector2f v) {position += v;}
void GameSprite::GameTransform::Move(Vector2f v, BoxType boxType) {
	Vector2f* _offsetBox = &OffsetHitBox;
	switch (boxType)
	{
		case BoxType::HitBox:
			OffsetHitBox += v;
			break;
		case BoxType::RenderBox:
			OffsetRenderBox += v;
			break;
		case BoxType::PseudoRenderBox:
			OffsetPseudoRenderBox += v;
			break;
	}
}
void GameSprite::GameTransform::SetScale(Vector2f v) {scale = v;}
void GameSprite::GameTransform::SetPosition(float x, float y) {	position = Vector2f(x, y);}
void GameSprite::GameTransform::SetPosition(Vector2f v) { position = v; }
void GameSprite::GameTransform::SetPositionOffset(Vector2f v, BoxType boxType) {
	switch (boxType)
	{
		case RenderBox:
			OffsetRenderBox = v;
			break;
		case HitBox:
			OffsetHitBox = v;
			break;
		case PseudoRenderBox:
			OffsetPseudoRenderBox  = v;
			break;
	}
}
void GameSprite::GameTransform::SetParent(weak_ptr<GameSprite> parent) {
	if (parent.expired()) {
		printf("parent is null please add value\n");
		return;
	}
	if (!this->parent.expired()) {
		this->parent.lock()->transform->childs[childIndex].reset();
	}
	shared_ptr<GameSprite> sp = parent.lock();
	this->parent = parent;
	sp->transform->childs.push_back(this->wp);
	this->childIndex = (int)sp->transform->childs.size() - 1;
}
GameSprite::GameTransform::GameTransform() {};
GameSprite::GameTransform::~GameTransform() {}
void GameSprite::GameTransform::Printing() {
	printf("game transform 1");
}
void GameSprite::GameTransform::SetSpriteOffset(const SpriteOffsetData& spriteOffsetData) {
	{
		renderBox.setTextureRect(IntRect(spriteOffsetData.startPixel, spriteOffsetData.renderPixelSize));
		SetSize((Vector2f)spriteOffsetData.renderPixelSize * spriteOffsetData.scale, BoxType::RenderBox);
		SetSize((Vector2f)spriteOffsetData.renderPixelSize * spriteOffsetData.scale, BoxType::PseudoRenderBox);
		SetSize(spriteOffsetData.hitBoxSize * spriteOffsetData.scale, BoxType::HitBox);
		hitBox.setFillColor(Color::Blue);
		SetPositionOffset(spriteOffsetData.hitboxOffset * spriteOffsetData.scale + spriteOffsetData.allOffset, HitBox);
		SetPositionOffset(spriteOffsetData.allOffset, RenderBox);
		SetPositionOffset(spriteOffsetData.allOffset, PseudoRenderBox);
		SetAnchorType(AnchorType::DownCentor, HitBox, FIX_ALL_RECT_POSITION);
	}
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>GameSprite<<<<<<<<<<<<<<<<<<<<<<<<
GameSprite::GameSprite() {}
GameSprite::GameSprite(std::string s) : name(s) { }
GameSprite::~GameSprite() {
	//cout << name << " has been destroy" << endl;
	for (int i = 0; i < transform->childs.size(); i++) {
		if (!transform->childs[i].expired()) {
			type_index typeIndex = transform->childs[i].lock()->transform->typeIndex;
			Destroy(transform->childs[i], typeIndex);
		}
	}
}
void GameSprite::SetTransform(weak_ptr<GameSprite> wp, type_index typeIndex) {
	if (wp.expired()) {
		printf("wp is null please add value");
		return;
	}
	transform->wp = wp;
	transform->typeIndex = typeIndex;
	if (!WorldControl::Hierarchy().expired()) {
		transform->SetParent(WorldControl::Hierarchy());
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
void MoveAllSprites(weak_ptr<GameSprite> a, int b, Vector2f realWorldPosition, Vector2f realWorldScale) {
	vector< weak_ptr<GameSprite> > v;
	shared_ptr<GameSprite> sp = a.lock();
	realWorldPosition += Multiple(sp->transform->position, realWorldScale);
	sp->transform->renderBox.setPosition(realWorldPosition + Multiple(sp->transform->OffsetRenderBox, realWorldScale, sp->transform->scale));
	sp->transform->pseudoRenderBox.setPosition(realWorldPosition + Multiple(sp->transform->OffsetPseudoRenderBox, realWorldScale, sp->transform->scale));
	sp->transform->hitBox.setPosition(realWorldPosition + Multiple(sp->transform->OffsetHitBox, realWorldScale, sp->transform->scale));
	sp->transform->renderBox.setScale(sp->transform->scale);
	sp->transform->pseudoRenderBox.setScale(sp->transform->scale);
	sp->transform->hitBox.setScale(sp->transform->scale);
	for (int i = 0; i < sp->transform->childs.size(); i++) {
		if (!sp->transform->childs[i].expired()) {
			MoveAllSprites(sp->transform->childs[i], b + 1, realWorldPosition, Multiple(sp->transform->scale, realWorldScale));
			v.push_back(sp->transform->childs[i]);
			sp->transform->childs[i].lock()->transform->childIndex = (int)v.size() - 1;
		}
	}
	sp->transform->childs = v;
}
void DrawAllSprites(weak_ptr<GameSprite> a) {
	vector< weak_ptr<GameSprite> > v;
	shared_ptr<GameSprite> sp = a.lock();
	//WorldControl::window().draw(sp->transform.hitBox);
	WorldControl::window().draw(sp->transform->renderBox);
	for (int i = 0; i < sp->transform->childs.size(); i++) {
		if (!sp->transform->childs[i].expired()) {
			DrawAllSprites(sp->transform->childs[i]);
		}
	}
}
void MoveAndDrawAllSprites(weak_ptr<GameSprite> a, int b,Vector2f realWorldPosition,Vector2f realWorldScale) {
	vector< weak_ptr<GameSprite> > v;
	shared_ptr<GameSprite> sp=a.lock();
	realWorldPosition += Multiple(sp->transform->position, realWorldScale);
	sp->transform->hitBox.setPosition(realWorldPosition + Multiple(sp->transform->OffsetHitBox, realWorldScale, sp->transform->scale));
	sp->transform->renderBox.setPosition(realWorldPosition+Multiple(sp->transform->OffsetRenderBox,realWorldScale, sp->transform->scale) );
	sp->transform->pseudoRenderBox.setPosition(realWorldPosition + Multiple(sp->transform->OffsetPseudoRenderBox, realWorldScale, sp->transform->scale));
	sp->transform->hitBox.setScale(sp->transform->scale);
	sp->transform->renderBox.setScale(sp->transform->scale);
	sp->transform->pseudoRenderBox.setScale(sp->transform->scale);
	WorldControl::window().draw(sp->transform->hitBox);
	WorldControl::window().draw(sp->transform->renderBox);
	WorldControl::window().draw(sp->transform->pseudoRenderBox);
	for (int i = 0; i < sp->transform->childs.size(); i++) {
		if (!sp->transform->childs[i].expired()) {
			MoveAndDrawAllSprites(sp->transform->childs[i], b + 1,realWorldPosition,Multiple(sp->transform->scale , realWorldScale));
			v.push_back(sp->transform->childs[i]);
			sp->transform->childs[i].lock()->transform->childIndex = (int)v.size() - 1;
		}
	}
	sp->transform->childs = v;
}
void CheckAllSpriteName(weak_ptr<GameSprite> a, int b) {
	for (int i = 0; i < b; i++) { printf("\t"); }
	cout << a.lock()->name << endl;
	vector< weak_ptr<GameSprite> > v;
	shared_ptr<GameSprite> sp = a.lock();
	for (int i = 0; i < sp->transform->childs.size(); i++) {
		if (!sp->transform->childs[i].expired()) {
			CheckAllSpriteName(sp->transform->childs[i], b + 1);
		}
	}
}

SpriteOffsetData::SpriteOffsetData(const Vector2i & startPixel, const Vector2i & renderPixelSize, const Vector2f hitBoxSize, const Vector2f & hitboxOffset, const Vector2f & allOffset, const float& scale) :
		startPixel(startPixel), renderPixelSize(renderPixelSize), hitBoxSize(hitBoxSize), hitboxOffset(hitboxOffset), allOffset(allOffset), scale(scale) {}
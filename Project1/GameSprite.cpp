#include "GameSprite.h"
#include "WorldControl.h"
#include <iostream>
Vector2f Multiple(Vector2f a, Vector2f b) {return Vector2f(a.x * b.x, a.y * b.y);}
Vector2f Multiple(Vector2f a, Vector2f b, Vector2f c) { return Vector2f(a.x * b.x*c.x, a.y * b.y*c.y); }
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>GameTransfrom<<<<<<<<<<<<<<<<<<<<<<<<
void GameSprite::GameTransform::SetSize(Vector2f v, BoxType boxType) {
	switch (boxType)
	{
	case RenderBox:
		renderBox.setSize(v);
		SetAnchorType(anchorType,boxType);
		break;
	case HitBox:
		hitBox.setSize(v);
		SetAnchorType(anchorType, boxType);
		break;
	default:
		SetAnchorType(anchorType, boxType);
		break;
	}
}
void GameSprite::GameTransform::SetAnchorType(AnchorType _anchor,BoxType boxType) {
	anchorType = _anchor;
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
	}
	RectangleShape& box = *_box;
	Vector2f& offsetBox = *_offsetBox;
	switch (_anchor)
	{
	case TopLeft:
		nPos=Vector2f(0,0);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		break;
	case TopCentor:
		nPos=Vector2f(box.getSize().x / 2, 0);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		break;
	case TopRight:
		nPos=Vector2f(box.getSize().x, 0);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		break;
	case MiddleLeft:
		nPos=Vector2f(0, box.getSize().y / 2);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		break;
	case MiddleCentor:
		nPos=Vector2f(box.getSize().x / 2, box.getSize().y / 2);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		break;
	case MiddleRight:
		nPos=Vector2f(box.getSize().x, box.getSize().y / 2);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		break;
	case DownLeft:
		nPos=Vector2f(0, box.getSize().y);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		break;
	case DownCentor:
		nPos=Vector2f(box.getSize().x / 2, box.getSize().y);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
		break;
	case DownRight:
		nPos=Vector2f(box.getSize().x, box.getSize().y);
		offsetBox += nPos - box.getOrigin();
		box.setOrigin(nPos);
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
	}
}
void GameSprite::GameTransform::SetScale(Vector2f v) {scale = v;}
void GameSprite::GameTransform::SetPosition(float x, float y) {	position = Vector2f(x, y);}
void GameSprite::GameTransform::SetPosition(Vector2f v) { position = v; }
void GameSprite::GameTransform::SetPosition(Vector2f v, BoxType boxType) {
	switch (boxType)
	{
		case RenderBox:
			OffsetRenderBox = v;
			break;
		case HitBox:
			OffsetHitBox = v;
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
/*GameSprite::GameTransform::GameTransform(Vector2f position, Vector2f scale, Vector2f hitboxPosition, Vector2f renderPosition)
	:position(position),scale(scale),OffsetHitBox(hitboxPosition),OffsetRenderBox(renderPosition) {}*/

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
	for (int i = 0; i < b; i++) { printf("\t"); }
	cout << a.lock()->name << endl;
	shared_ptr<GameSprite> sp = a.lock();
	realWorldPosition += Multiple(sp->transform->position, realWorldScale);
	sp->transform->renderBox.setPosition(realWorldPosition + Multiple(sp->transform->OffsetRenderBox, realWorldScale, sp->transform->scale));
	sp->transform->hitBox.setPosition(realWorldPosition + Multiple(sp->transform->OffsetHitBox, realWorldScale, sp->transform->scale));
	sp->transform->hitBox.setScale(sp->transform->scale);
	sp->transform->renderBox.setScale(sp->transform->scale);
	for (int i = 0; i < sp->transform->childs.size(); i++) {
		if (!sp->transform->childs[i].expired()) {
			MoveAllSprites(sp->transform->childs[i], b + 1, realWorldPosition, Multiple(sp->transform->scale, realWorldScale));
			v.push_back(sp->transform->childs[i]);
			sp->transform->childs[i].lock()->transform->childIndex = v.size() - 1;
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
	for (int i = 0; i < b; i++) { printf("\t"); }
		cout << a.lock()->name << endl;
	shared_ptr<GameSprite> sp=a.lock();
	realWorldPosition += Multiple(sp->transform->position, realWorldScale);
	sp->transform->renderBox.setPosition(realWorldPosition+Multiple(sp->transform->OffsetRenderBox,realWorldScale, sp->transform->scale) );
	sp->transform->hitBox.setPosition(realWorldPosition + Multiple(sp->transform->OffsetHitBox, realWorldScale, sp->transform->scale));
	sp->transform->hitBox.setScale(sp->transform->scale);
	sp->transform->renderBox.setScale(sp->transform->scale);
	WorldControl::window().draw(sp->transform->hitBox);
	WorldControl::window().draw(sp->transform->renderBox);
	for (int i = 0; i < sp->transform->childs.size(); i++) {
		if (!sp->transform->childs[i].expired()) {
			MoveAndDrawAllSprites(sp->transform->childs[i], b + 1,realWorldPosition,Multiple(sp->transform->scale , realWorldScale));
			v.push_back(sp->transform->childs[i]);
			sp->transform->childs[i].lock()->transform->childIndex = v.size() - 1;
		}
	}
	sp->transform->childs = v;
}
//cout <<"Position" << realWorldPosition.x << "....." << realWorldPosition.y << endl;
	//cout << "RenderBox" << WorldControl::player().lock()->transform.renderBox.getPosition().x << "....." << WorldControl::player().lock()->transform.renderBox.getPosition().y << endl;
	//cout << "HitBox" << WorldControl::player().lock()->transform.hitBox.getPosition().x << "....." << WorldControl::player().lock()->transform.hitBox.getPosition().y << endl<<endl;
	//cout << "scale:" << a.lock()->name<<endl;
	//cout << "position:" << a.lock()->transform.renderBox.getPosition().x << "........" << a.lock()->transform.renderBox.getPosition().y << endl;
	//cout << "origin:" << a.lock()->transform.renderBox.getOrigin().x << "........" << a.lock()->transform.renderBox.getOrigin().y << endl << endl;
/*NotUseNow
	GameSprite::GameSprite(std::string s, Vector2f position, Vector2f scale, Vector2f hitboxPosition, Vector2f renderPosition)
		:name(s),transform(position,scale,hitboxPosition,renderPosition) {}
	GameSprite::GameSprite(std::string s, Vector2f position, Vector2f scale) :
		name(s), transform(position, scale,Vector2f(0,0),Vector2f(0,0)) {}
	GameSprite::GameSprite(GameSprite& gameSprite)
		: name(gameSprite.name), transform(gameSprite.transform.position, gameSprite.transform.scale, gameSprite.transform.OffsetHitBox, gameSprite.transform.OffsetRenderBox) {}
	*/
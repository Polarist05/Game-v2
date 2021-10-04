#include "Tile.h"
#include<iostream>
#include "WorldControl.h"
//TileTransform
//Tile
Tile::Tile()
{
	transform = &m_transform;
}
Tile::Tile(std::string s) :GameSprite(s)
{
	transform = &m_transform;
}
Tile::TileTransform* Tile::GetTransform() { return &m_transform; }
Vector2f Tile::GetAreaSize() { return AreaSize; }
void Tile::SetAreaSize(Vector2f v) {AreaSize = v; printf("AreaSize:%f\t%f\n",AreaSize.x,AreaSize.y); }
Vector2f Tile::GetRealRoomSize() {
	return Multiple(Vector2f((RSIZEX + 2), (RSIZEY + 2)), GetAreaSize());
}
Vector2f Tile::GetRealPositionAt(const Vector2i& RoomPosition, const Vector2i& AreaPosition) {
	return Multiple(GetRealRoomSize() ,(Vector2f)RoomPosition)+Multiple(GetAreaSize(),(Vector2f)AreaPosition);
}
Vector2f Tile::GetRealPositionAt(const Vector2i& RoomPosition, const Vector2f& AreaPosition) {
	return Multiple(GetRealRoomSize(), (Vector2f)RoomPosition) + Multiple(GetAreaSize(), AreaPosition);
}

//--------------------------------------------------------------------------------------
//TilemapTransform
void Tilemap::TilemapTransform::SetParent(weak_ptr<GameSprite> tileParent)
{
	weak_ptr<Tile> wp = dynamic_pointer_cast<Tile>(tileParent.lock());
	if (wp.expired()) {
		if(!WControl::MainTile().expired())
			GameTransform::SetParent(NotrenderTile());
		else
			cout << "You can't set Tilemap parent to non-Tile Object" << endl;
		return;
	}
	SetParent( wp, Vector2i(0, 0));
}
void Tilemap::TilemapTransform::SetParent(weak_ptr<Tile> parent, Vector2i positionInTile) {
	if (!parent.expired()) {
		GameTransform::SetParent(parent);
		SetAllAreasSizeInTilemap();
	}
	else
		GameTransform::SetParent(NotrenderTile());
	SetPositionInTile(positionInTile);
	SetAllAreasPositionInTilemap();
}
void Tilemap::TilemapTransform::SetPosition(float x, float y)
{
	cout << "Tilemap can't set position" << endl;
}
void Tilemap::TilemapTransform::SetPosition(Vector2f v)
{
	cout << "Tilemap can't set position" << endl;
}
void  Tilemap::TilemapTransform::Move(Vector2f v)
{
	cout << "Tilemap can't Move" << endl;
}
void Tilemap::TilemapTransform::SetPositionInTile(Vector2i positionInTile) 
{
	this->positionInTile = positionInTile;
	position = Multiple(GetAreaSize(), (Vector2f)positionInTile);
}
weak_ptr<Tile> Tilemap::TilemapTransform::GetTile()
{
	return(dynamic_pointer_cast<Tile>(parent.lock()));
}
Vector2f Tilemap::TilemapTransform::GetAreaSize()
{
	return GetTile().lock()->GetAreaSize();
}
void Tilemap::TilemapTransform::SetAllAreasSizeInTilemap() {
	for (int i = 0; i < childs.size(); i++) {
		weak_ptr<Area> wp = dynamic_pointer_cast<Area>(childs[i].lock()->transform->wp.lock());
		if (!wp.expired()) {
			wp.lock()->GetTransform()->SetSize(wp.lock()->GetTransform()->GetAreaSize(),BoxType::RenderBox,FIX_ONLY_ANCHOR_POSITION);
		}
	}
}
void Tilemap::TilemapTransform::SetAllAreasPositionInTilemap() {
	for (int i = 0; i < childs.size(); i++) {
		weak_ptr<Area> wp = dynamic_pointer_cast<Area>(childs[i].lock()->transform->wp.lock());
		if (!wp.expired()) {
			wp.lock()->GetTransform()->SetPositionInTilemap(wp.lock()->GetTransform()->GetPositionInTilemap());
		}
	}
}
//Tilemap
Tilemap::Tilemap()
{
	transform = &m_transform;
}
Tilemap::Tilemap(std::string s) :GameSprite(s)
{
	transform = &m_transform;
}
Tilemap::TilemapTransform* Tilemap::GetTransform() { return &m_transform; }
void Tilemap::SetTransform(weak_ptr<GameSprite> wp, type_index typeIndex) 
{
	if (wp.expired()) {
		printf("wp is null please add value");
		return;
	}
	transform->wp = wp;
	transform->typeIndex = typeIndex;
	if (!WControl::NotrenderTile().expired()) {
		transform->SetParent(WControl::NotrenderTile());
	}
}


//----------------------------------------------------------------------------------
//AreaTransform
void Area::AreaTransform::SetParent(weak_ptr<GameSprite> tilemapParent)
{
	weak_ptr<Tilemap> wp = dynamic_pointer_cast<Tilemap>(tilemapParent.lock());
	if (wp.expired()) {
		cout << "You can't set Area parent to non-Tilemap Object" << endl;
		return;
	}
	SetParent(wp, positionInTilemap); 
}
void Area::AreaTransform::SetParent(weak_ptr<Tilemap> tileParent, Vector2i positionInTile) {
	weak_ptr<Tilemap>  wp = dynamic_pointer_cast<Tilemap>(tileParent.lock());
	if (!wp.expired()) {
		GameTransform::SetParent(tileParent);
	}
	else {
		GameTransform::SetParent(NotrenderTilemap());
	}
	SetPositionInTilemap(positionInTile);
}
void Area::AreaTransform::SetPosition(float x, float y)
{
	cout << "Area can't set position" << endl;
}
void Area::AreaTransform::SetPosition(Vector2f v)
{
	cout << "Area can't set position" << endl;
}

void Area::AreaTransform::SetAll(weak_ptr<Tilemap> tileParent, Vector2i positionInTile,RenderPriorityType RenderPriority) {
	SetParent(tileParent, positionInTile);
	this->RenderPriority = RenderPriority;
	//renderBox.setFillColor(Color::Cyan);
	SetSize(GetAreaSize(), BoxType::RenderBox, FIX_ONLY_ANCHOR_POSITION);
}
void Area::AreaTransform::SetAll(weak_ptr<Tilemap> tileParent, Vector2i positionInTile, RenderPriorityType RenderPriority,Color color) {
	SetParent(tileParent, positionInTile);
	this->RenderPriority = RenderPriority;
	renderBox.setFillColor(color);
	SetSize(GetAreaSize(), BoxType::RenderBox, FIX_ONLY_ANCHOR_POSITION);
}
void Area::AreaTransform::SetAll(weak_ptr<Tilemap> tileParent, Vector2i positionInTile,Vector2f renderSize, RenderPriorityType RenderPriority) {
	SetParent(tileParent, positionInTile);
	this->RenderPriority = RenderPriority;
	//renderBox.setFillColor(Color::Cyan);
	SetSize(renderSize, BoxType::RenderBox, FIX_ONLY_ANCHOR_POSITION);
}
void Area::AreaTransform::SetAll(weak_ptr<Tilemap> tileParent, Vector2i positionInTile, Vector2f renderSize, RenderPriorityType RenderPriority, Color color) {
	SetParent(tileParent, positionInTile);
	this->RenderPriority = RenderPriority;
	renderBox.setFillColor(color);
	SetSize(renderSize, BoxType::RenderBox, FIX_ONLY_ANCHOR_POSITION);
}

void Area::AreaTransform::Move(Vector2f v)
{
	cout << "Area can't Move" << endl;
}
void Area::AreaTransform::SetPositionInTilemap(Vector2i positionInTilemap) 
{
	this->positionInTilemap = positionInTilemap;
	Vector2f v = Multiple(GetAreaSize(), (Vector2f)positionInTilemap); 
	position = v;
}
Vector2i Area::AreaTransform::GetPositionInTilemap() { return positionInTilemap; }
weak_ptr<Tilemap> Area::AreaTransform::GetTilemap() {
	weak_ptr < Tilemap > wp = dynamic_pointer_cast<Tilemap>(parent.lock());
	return wp;
}
weak_ptr<Tile> Area::AreaTransform::GetTile()
{
	return dynamic_pointer_cast<Tile>(GetTilemap().lock()->transform->parent.lock());
}
Vector2f Area::AreaTransform::GetAreaSize() 
{
	return GetTile().lock()->GetAreaSize();
}
//Area
Area::Area()
{
	transform = &m_transform;
}
Area::Area(std::string s) :GameSprite(s)
{
	transform = &m_transform;
}
Area::AreaTransform* Area::GetTransform() {return &m_transform; }
void Area::SetTransform(weak_ptr<GameSprite> wp, type_index typeIndex) {
	if (wp.expired()) {
		printf("wp is null please add value");
		return;
	}
	transform->wp = wp;
	transform->typeIndex = typeIndex;
	if (!WControl::NotrenderTilemap().expired()) {
		transform->SetParent(WControl::NotrenderTilemap());
	}
}

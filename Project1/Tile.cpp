#include "Tile.h"
#include<iostream>
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
void Tile::SetAreaSize(Vector2f v) { AreaSize = v; printf("AreaSize:%f\t%f\n",AreaSize.x,AreaSize.y); }

//--------------------------------------------------------------------------------------
//TilemapTransform
void Tilemap::TilemapTransform::SetParent(weak_ptr<GameSprite> parent)
{
	SetParent(dynamic_pointer_cast<Tile>(parent.lock()) , Vector2i(0, 0));
}
void Tilemap::TilemapTransform::SetParent(weak_ptr<Tile> parent, Vector2i positionInTile) {
	if (!parent.expired())
		GameTransform::SetParent(parent);
	else
		GameTransform::SetParent(NotrenderTile());
	SetPositionInTile(positionInTile);
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



//----------------------------------------------------------------------------------
//AreaTransform
void Area::AreaTransform::SetParent(weak_ptr<GameSprite> parent){ SetParent(parent, positionInTile); }
void Area::AreaTransform::SetParent(weak_ptr<GameSprite> parent, Vector2i positionInTile) {
	weak_ptr<Tilemap>  wp = dynamic_pointer_cast<Tilemap>(parent.lock());
	if (!wp.expired())
		GameTransform::SetParent(parent);
	else
		GameTransform::SetParent(NotrenderTilemap());
	SetPositionInTile(positionInTile);
}
void Area::AreaTransform::SetPosition(float x, float y)
{
	cout << "Area can't set position" << endl;
}
void Area::AreaTransform::SetPosition(Vector2f v)
{
	cout << "Area can't set position" << endl;
}
void Area::AreaTransform::Move(Vector2f v)
{
	cout << "Area can't Move" << endl;
}
void Area::AreaTransform::SetPositionInTile(Vector2i positionInTile) 
{
	this->positionInTile = positionInTile;
	position = Multiple(GetAreaSize() , (Vector2f)positionInTile);
}
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

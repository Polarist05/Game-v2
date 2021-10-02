#pragma once
#include "GameSprite.h"
Vector2f Multiple(const Vector2f& a, const Vector2f& b);
class Tile :public GameSprite 
{
	class TileTransform :public GameTransform {};
	TileTransform m_transform;
	Vector2f AreaSize = Vector2f(0, 0);
	Vector2f GetRealRoomSize();
public:
	Tile();
	Tile(std::string s);
	TileTransform* GetTransform();
	Vector2f GetAreaSize();
	void SetAreaSize(Vector2f v);
	Vector2f GetRealPositionAt(Vector2i RoomPosition, Vector2i AreaPosition);
};
class Tilemap :public GameSprite 
{	
	class TilemapTransform :public GameTransform {
		weak_ptr<Tile> NotrenderTile();
		Vector2i positionInTile;
	public:
		void SetParent(weak_ptr<GameSprite> parent)override;
		void SetParent(weak_ptr<Tile> parent, Vector2i positionInTile);
		void SetPosition(float x, float y)override;
		void SetPosition(Vector2f v)override;
		void Move(Vector2f v)override;
		void SetPositionInTile(Vector2i);
		void SetAllAreasSizeInTilemap();
		void SetAllAreasPositionInTilemap();
		weak_ptr<Tile> GetTile();
		Vector2f GetAreaSize();
	};
	TilemapTransform m_transform;
public:	
	Tilemap();
	Tilemap(std::string s);
	TilemapTransform* GetTransform();
protected:
	void SetTransform(weak_ptr<GameSprite> wp, type_index typeIndex) override;
};
class Area :public GameSprite {
	class AreaTransform :public GameTransform
	{
		weak_ptr<Tilemap> NotrenderTilemap();
		Vector2i positionInTilemap= Vector2i(0,0);
	public:
		void SetParent(weak_ptr<GameSprite> parent)override;
		void SetParent(weak_ptr<Tilemap> parent, Vector2i positionInTile);
		void SetPosition(float x, float y)override;
		void SetPosition(Vector2f v)override;
		void Move(Vector2f v)override;
		void SetPositionInTilemap(Vector2i);
		Vector2i GetPositionInTilemap();
		weak_ptr<Tilemap> GetTilemap();
		weak_ptr<Tile> GetTile();
		Vector2f GetAreaSize();
	};
	AreaTransform m_transform;
public:
	Area();
	Area(std::string s);
	AreaTransform* GetTransform();
protected:
	void SetTransform(weak_ptr<GameSprite> wp, type_index typeIndex) override;
};
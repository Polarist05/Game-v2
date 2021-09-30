#pragma once
#include "GameSprite.h"
Vector2f Multiple(Vector2f a, Vector2f b);
class Tile :public GameSprite 
{
	class TileTransform :public GameTransform {};
	TileTransform m_transform;
	Vector2f AreaSize = Vector2f(0, 0);
public:
	Tile();
	Tile(std::string s);
	TileTransform* GetTransform();
	Vector2f GetAreaSize();
	void SetAreaSize(Vector2f v);
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
		weak_ptr<Tile> GetTile();
		Vector2f GetAreaSize();
	};
	TilemapTransform m_transform;
public:	
	Tilemap();
	Tilemap(std::string s);
	TilemapTransform* GetTransform();
};
class Area :public GameSprite {
	class AreaTransform :public GameTransform
	{
		weak_ptr<Tilemap> NotrenderTilemap();
		Vector2i positionInTile;
	public:
		void SetParent(weak_ptr<GameSprite> parent)override;
		void SetParent(weak_ptr<GameSprite> parent, Vector2i positionInTile);
		void SetPosition(float x, float y)override;
		void SetPosition(Vector2f v)override;
		void Move(Vector2f v)override;
		void SetPositionInTile(Vector2i);
		weak_ptr<Tilemap> GetTilemap();
		weak_ptr<Tile> GetTile();
		Vector2f GetAreaSize();
	};
	AreaTransform m_transform;
public:
	Area();
	Area(std::string s);
	AreaTransform* GetTransform();
};
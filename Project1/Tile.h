#pragma once
#include "GameSprite.h"
Vector2f Multiple(const Vector2f& a, const Vector2f& b);
class Tile :public GameSprite 
{
	class TileTransform :public GameTransform {};
	TileTransform m_transform;
	Vector2f AreaSize = Vector2f(0, 0);
	
public:
	Tile();
	Tile(std::string s);
	Vector2f GetRealRoomSize();
	TileTransform* GetTransform();
	static const Vector2f& GetAreaSize();
	Vector2f GetRealPositionAt(const Vector2i& RoomPosition, const Vector2i& AreaPosition);
	Vector2f GetRealPositionAt(const Vector2i& RoomPosition, const Vector2f& AreaPosition);
};
class Tilemap :public GameSprite 
{	
	class TilemapTransform :public GameTransform {
		weak_ptr<Tile> NotrenderTile();
		Vector2i positionInTile;
	public:
		const Vector2i GetPositionInTileAt(const Vector2f& pos);
		const Vector2f GetRealPositionAt(const Vector2i& pos);
		void SetParent(weak_ptr<GameSprite> parent)override;
		void SetParent(weak_ptr<Tile> parent, Vector2i positionInTile);
		//void GetPosition()
		void SetPosition(float x, float y)override;
		void SetPosition(Vector2f v)override;
		
		//void SetPosition(Vector2f v,BoxType) override;
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
		void SetAll(weak_ptr<Tilemap> tileParent,const Vector2i& positionInTile, RenderPriorityType RenderPriority);
		void SetAll(weak_ptr<Tilemap> tileParent,const Vector2i& positionInTile, RenderPriorityType RenderPriority, Color color);
		void SetAll(weak_ptr<Tilemap> tileParent,const Vector2i& positionInTile, Vector2f renderSize, RenderPriorityType RenderPriority);
		void SetAll(weak_ptr<Tilemap> tileParent,const Vector2i& positionInTile, Vector2f renderSize, RenderPriorityType RenderPriority, Color color);
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
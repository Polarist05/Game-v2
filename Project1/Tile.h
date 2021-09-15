#pragma once
#include "GameSprite.h"
#include<iostream>
Vector2f Multiple(Vector2f a, Vector2f b);
class Tile :public GameSprite 
{
	class TileTransform :public GameTransform 
	{
	public:
		//void SetParent(weak_ptr<GameSprite>)override {}
		//void SetPosition(float x, float y)override {}
		//void SetPosition(Vector2f v)override {}
		//void virtual Move(Vector2f v)override {}
	};
	TileTransform m_transform;
public:
	Vector2f AreaSize=Vector2f(0,0);
	Tile() 
	{
		transform = &m_transform;
	}
};
class Tilemap :public GameSprite 
{	
	class TilemapTransform :public GameTransform {
		weak_ptr<Tile> NotrenderTile();
		Vector2i positionInTile;
	public:
		void SetParent(weak_ptr<GameSprite> parent)override 
		{
			SetParent(parent, Vector2i(0, 0) );
		}
		void SetParent(weak_ptr<GameSprite> parent, Vector2i positionInTile) {
			weak_ptr<Tile> wp = dynamic_pointer_cast<Tile>(parent.lock());
			if(!wp.expired())
				GameTransform::SetParent(parent);
			else
				GameTransform::SetParent(NotrenderTile());
			SetPositionInTile(positionInTile);
		}
		void SetPosition(float x, float y)override 
		{
			cout << "Tilemap can't set position" << endl;
		}
		void SetPosition(Vector2f v)override 
		{
			cout << "Tilemap can't set position" << endl;
		}
		void virtual Move(Vector2f v)override 
		{
			cout << "Tilemap can't Move" << endl;
		}
		void SetPositionInTile(Vector2i) {
			weak_ptr<Tile> wp = GetTile();
			if (!wp.expired()) 
			{
				 position = Multiple(wp.lock()->AreaSize , (Vector2f)positionInTile);
			}
			else
			{
				cout << "Parent is not a Tile" << endl;
			}
		}
		weak_ptr<Tile> GetTile() 
		{
			return(dynamic_pointer_cast<Tile>(parent.lock()));
		}
	};
	TilemapTransform m_transform;
public:	
	Tilemap() 
	{
		transform = &m_transform;
	}
};
class Area :public GameSprite {
	class AreaTransform :public GameTransform
	{
		weak_ptr<Tilemap> NotrenderTilemap();
		Vector2i positionInTile;
	public:
		void SetParent(weak_ptr<GameSprite> parent)override
		{
			SetParent(parent,Vector2i(0,0));
		}
		void SetParent(weak_ptr<GameSprite> parent, Vector2i positionInTile) {
			weak_ptr<Tilemap>  wp = dynamic_pointer_cast<Tilemap>(parent.lock());
			if (!wp.expired()) 
				GameTransform::SetParent(parent);
			else
				GameTransform::SetParent(NotrenderTilemap());
				SetPositionInTile(positionInTile);
		}
		void SetPosition(float x, float y)override
		{
			cout << "Area can't set position" << endl;
		}
		void SetPosition(Vector2f v)override
		{
			cout << "Area can't set position" << endl;
		}
		void virtual Move(Vector2f v)override
		{
			cout << "Area can't Move" << endl;
		}
		void SetPositionInTile(Vector2i) {
			weak_ptr<Tile> wp = GetTile();
			if (!wp.expired())
			{
				position = Multiple(wp.lock()->AreaSize, (Vector2f)positionInTile);
			}
			else
			{
				cout << "Parent is not a Tile" << endl;
			}
		}
		weak_ptr<Tilemap> GetTilemap() {
			weak_ptr < Tilemap > wp = dynamic_pointer_cast<Tilemap>(parent.lock());
			return wp;
		}
		weak_ptr<Tile> GetTile()
		{
			//weak_ptr < Tilemap > wp = ;
			//weak_ptr < Tile > wp1 = ;
			return dynamic_pointer_cast<Tile>(GetTilemap().lock()->transform->parent.lock());
		}
	};
	AreaTransform m_transform;
public:
	Area() 
	{
		transform = &m_transform;
	}	
	/*void transform::SetParent(weak_ptr<GameSprite>) override {}
	void virtual SetPosition(float x, float y);
	void virtual SetPosition(Vector2f v);
	void virtual Move(Vector2f v);*/
};
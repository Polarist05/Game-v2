#pragma once
#include "Room.h"
#include "GameSprite.h"
#include "Dungeon.h"
class GameRenderer
{
	static RenderWindow& window();
	static weak_ptr<GameSprite> player();
	static weak_ptr<GameSprite>Hierachy();
	static void FindPlayerAndObject(weak_ptr<GameSprite> a, vector<weak_ptr<GameSprite> >& v, vector<pair<float, int > >& v1);
public:
	static void RenderAll();
	static void RenderWallAndFloor();
	static void RenderKnife();
	static void RenderPlayerAndObject();	
	static void RenderUI();
	static void RenderUX();
	static void RenderSettingView();
	static void RenderAreaHilight();
	static void Renderfireflies();
	
private:
	static void RenderEdge();
	static void RenderFloorAt(weak_ptr<Room> rederRoom);
	static void RenderWallAt(weak_ptr<Room> renderRoom);
};


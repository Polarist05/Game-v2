#pragma once
#include "Room.h"
#include "GameSprite.h"
#include "Dungeon.h"
class GameRenderer
{
	RenderWindow& window();
	weak_ptr<GameSprite> player();
	weak_ptr<GameSprite>Hierachy();
	void FindPlayerAndObject(weak_ptr<GameSprite> a, vector<weak_ptr<GameSprite> >& v, vector<pair<float, int > >& v1);
public:
	void RenderAll();
	void RenderWallAndFloor();
	void RenderKnife();
	void RenderPlayerAndObject();	
	void RenderUI();
	void RenderUX();
	void RenderSettingView();
	

private:
	void RenderAreaHilight();
	void RenderEdge();
	void RenderFloorAt(weak_ptr<Room> rederRoom);
	void RenderWallAt(weak_ptr<Room> renderRoom);
};


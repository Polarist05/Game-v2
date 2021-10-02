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
	weak_ptr<Room> room;
	weak_ptr<Room> subRoom[4];
	void SetRenderRoom(weak_ptr<Room> room);
	void SetSubRenderRoom(weak_ptr<Room>* room);
	void RenderAll();
	void RenderWallAndFloor();
	void RenderKnife();
	void RenderPlayerAndObject();
	void RenderUI();
	void RenderSettingView();
	

private:
	void RenderFloorAt(weak_ptr<Room> rederRoom);
};


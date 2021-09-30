#pragma once
#include "Room.h"
#include "GameSprite.h"
class GameRenderer
{
	RenderWindow& window();
	weak_ptr<GameSprite> player();
	weak_ptr<GameSprite>Hierachy();
	void FindPlayerAndObject(weak_ptr<GameSprite> a, vector<weak_ptr<GameSprite> >& v, vector<pair<float, int > >& v1) {
		shared_ptr<GameSprite> sp = a.lock();
		if (sp->transform->RenderPriority == RenderPriorityType::PlayerAndObject) {
			v.push_back(a);
			v1.push_back({ sp->transform->renderBox.getPosition().y,v1.size() });
		}
		for (int i = 0; i < sp->transform->childs.size(); i++) {
			if (!sp->transform->childs[i].expired()) {
				FindPlayerAndObject(sp->transform->childs[i], v, v1);
			}
		}
	}
public:
	weak_ptr<Room> room;
	weak_ptr<Room> subRoom[4];
	void SetRenderRoom(weak_ptr<Room> room) { this->room = room; }
	void SetSubRenderRoom(weak_ptr<Room> *room) { for(int i=0;i<4;i++) subRoom[i] = room[i]; }
	void RenderAll() {
		RenderWallAndFloor();
		//RenderKnife();
		RenderPlayerAndObject();
		//RenderUI();
		//RenderSettingView();
	}
	void RenderWallAndFloor()
	{
		if (!room.expired()) {
			for (int i = 0; i < RSIZEY; i++)
			{
				for (int j = 0; j < RSIZEX; j++) {
					window().draw(room.lock()->areas[j][i].lock()->transform->renderBox);
				}
			}
		}
		for (int k = 0; k < 4; k++) {
			if (!subRoom[k].expired()) {
				for (int i = 0; i < RSIZEY; i++)
				{
					for (int j = 0; j < RSIZEX; j++) {
						window().draw(subRoom[k].lock()->areas[j][i].lock()->transform->renderBox);
					}
				}
			}
		}
	}
	void RenderKnife() {}
	void RenderPlayerAndObject() 
	{
		vector<weak_ptr<GameSprite> > v;
		vector<pair<float, int > > v1;
		FindPlayerAndObject(Hierachy(), v,v1);
		sort(v1.begin(),v1.end());
		for (int i = 0; i < v.size(); i++)
		{
			window().draw(v[v1[i].second].lock()->transform->renderBox);
		}
	}
	void RenderUI() {}
	void RenderSettingView() {}
	
};


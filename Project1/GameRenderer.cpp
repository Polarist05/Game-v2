#include "GameRenderer.h"
#include "WorldControl.h"
#include <iostream>
void GameRenderer::FindPlayerAndObject(weak_ptr<GameSprite> a, vector<weak_ptr<GameSprite> >& v, vector<pair<float, int > >& v1) {
	shared_ptr<GameSprite> sp = a.lock();
	if (sp->transform->RenderPriority == RenderPriorityType::PlayerAndObject) {
		v.push_back(a);
		v1.push_back({ sp->transform->hitBox.getPosition().y,v1.size() });
	}
	for (int i = 0; i < sp->transform->childs.size(); i++) {
		if (!sp->transform->childs[i].expired()) {
			FindPlayerAndObject(sp->transform->childs[i], v, v1);
		}
	}
}
void GameRenderer::RenderAll() {
	window().draw(WControl::GetCurrentRoom().lock()->GetTransform()->renderBox);
	RenderWallAndFloor();
	//RenderKnife();
	RenderPlayerAndObject();
	//RenderUI();
	//RenderSettingView();

}
void GameRenderer::RenderWallAndFloor()
{
	if (WorldControl::isGamePlaying()) {
		RenderFloorAt(WControl::GetCurrentRoom());
		RenderWallAt(WControl::GetCurrentRoom());
		int y = WControl::GetCurrentRoomPosition().y, x = WControl::GetCurrentRoomPosition().x;
		if (y + 1 < 5) {
			RenderFloorAt(WControl::getMainDungeon().Rooms[y + 1][x]);
			RenderWallAt(WControl::getMainDungeon().Rooms[y + 1][x]);
		}
		if (y - 1 >= 0) {
			RenderFloorAt(WControl::getMainDungeon().Rooms[y - 1][x]);
			RenderWallAt(WControl::getMainDungeon().Rooms[y - 1][x]);
		}
		if (x + 1 < 5) {
			RenderFloorAt(WControl::getMainDungeon().Rooms[y][x + 1]);
			RenderWallAt(WControl::getMainDungeon().Rooms[y][x+1]);
		}
		if (x - 1 >= 0) {
			RenderFloorAt(WControl::getMainDungeon().Rooms[y][x - 1]);
			RenderWallAt(WControl::getMainDungeon().Rooms[y ][x-1]);
		}
		RenderEdge();
	}
}
void GameRenderer::RenderEdge() {
	for (size_t i = 0; i < WControl::getMainDungeon().EdgeFloors.size(); i++) {
		window().draw(WControl::getMainDungeon().EdgeFloors[i].lock()->GetTransform()->renderBox);
	}
}
void GameRenderer::RenderFloorAt(weak_ptr<Room> renderRoom) {
	if (!renderRoom.expired()) {
		for (int i = 0; i < RSIZEY; i++)
		{
			for (int j = 0; j < RSIZEX; j++) {
				window().draw(renderRoom.lock()->areas[i][j].lock()->transform->renderBox);
			}
		}
	}
}
void GameRenderer::RenderWallAt(weak_ptr<Room> renderRoom) {
	for (int i = 0; i < renderRoom.lock()->Walls.size(); i++) {
		window().draw(renderRoom.lock()->Walls[i].lock()->GetTransform()->renderBox);
	}
}
void GameRenderer::RenderKnife() {}
void GameRenderer::RenderPlayerAndObject()
{
	vector<weak_ptr<GameSprite> > v;
	vector<pair<float, int > > v1;
	FindPlayerAndObject(Hierachy(), v, v1);
	sort(v1.begin(), v1.end());
	for (int i = 0; i < v.size(); i++)
	{
		window().draw(v[v1[i].second].lock()->transform->pseudoRenderBox);
		window().draw(v[v1[i].second].lock()->transform->hitBox);
		window().draw(v[v1[i].second].lock()->transform->renderBox);
	}
	window().draw(WControl::player().lock()->hookGuideLine);
}
void GameRenderer::RenderUI() {}
void GameRenderer::RenderSettingView() {}
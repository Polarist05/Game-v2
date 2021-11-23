#include "Update.h"
#include "Player.h"
#include "Room.h"
#include "UX.h"
#include "UI.h"
#include "WorldControl.h"
#include "Collision.h"
void Update::UpdatePlayer() {
	WControl::player().lock()->Update();
}
void Update::UpdateUX() {
	WControl::GetUX().lock()->Update();
}
void Update::UpdateKnife() {
	auto q = WControl::player().lock()->knifes;
	while (!q.empty())
	{
		if (!q.front().expired()) 
			q.front().lock()->Update();
		q.pop();
	}
}
void Update::UpdateRoom() {
	WControl::GetCurrentRoom().lock()->Update();
}
void Update::UpdateObject() {
	for (auto& wp : WControl::GetCurrentRoom().lock()->Objects) {
		for (auto& wp1 : wp.second) {
			if(!wp1.expired())
				wp1.lock()->Update();
		}
	}
}
void Update::UpdateUI() {
	UI::CheckUICollision();
}

void Update::UpdateFireFlies()
{
	static time_t t;
	static vector<Vector2f> v = vector<Vector2f>(7,Vector2f(0,0));
	if (clock()>t+200) {
		t = clock();
		v.clear();
		for (int i = 0; i < 7; i++)
		{
			v.push_back(Multiple(Vector2f(((float)(rand() % 100) - 50) / 50., ((float)(rand() % 100) - 50) / 50.), Vector2f(2, 2)));
		}
	}
	int i = 0;
	for(auto& wp:WControl::GetCurrentRoom().lock()->fireflies)
	{
		if (!wp.expired())
		{
			wp.lock()->transform->Move(v[i]);
			if (Collision::isCollision(wp.lock()->transform->renderBox, WControl::player().lock()->transform->pseudoRenderBox))
			{
				auto wp1=wp.lock()->transform->wp;
				auto index = wp.lock()->transform->typeIndex;
				WControl::player().lock()->IncreaseScore(10);
				Destroy(wp1, index);
				i++;
				continue;
			}
			for (auto& wp1 : WControl::GetCurrentRoom().lock()->Walls[4]) 
			{
				if (!wp.expired()&&!wp1.expired())
				{
					if (Collision::isCollision(wp.lock()->transform->renderBox, wp1.lock()->transform->renderBox))
					{
						auto wp2 = wp.lock()->transform->wp;
						auto index = wp.lock()->transform->typeIndex;
						Destroy(wp2, index);
					}
				}
			}
		}
		i++;
	}
}

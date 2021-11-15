#include "Update.h"
#include "Player.h"
#include "Room.h"
#include "UX.h"
#include "UI.h"
#include "WorldControl.h"
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
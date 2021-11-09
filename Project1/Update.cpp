#include "Player.h"
#include "Room.h"
#include "UX.h"
#include "UI.h"
#include "WorldControl.h"
void UpdatePlayer() {
	WControl::player().lock()->Update();
}
void UpdateUX() {
	WControl::GetUX().lock()->Update();
}
void UpdateKnife() {
	auto q = WControl::player().lock()->knifes;
	while (!q.empty())
	{
		q.front().lock()->Update();
		q.pop();
	}
}
void UpdateRoom() {
	WControl::GetCurrentRoom().lock()->Update();
}
void UpdateObject() {
	for (auto& wp : WControl::GetCurrentRoom().lock()->Objects) {
		for (auto& wp1 : wp.second) {
			wp1.lock()->Update();
		}
	}
}
void UpdateUI() {
	UI::CheckUICollision();
}
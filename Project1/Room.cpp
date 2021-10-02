#include "Room.h"
#include "Collision.h"
#include "WorldControl.h"
#include "Dungeon.h"
#include <iostream>
#include <time.h>
Room::Room() {}
Room::Room(std::string s) :Tilemap(s) {}
void Room::SetRoom() {
	SetFloor();
	
}
void Room::SetFloor() 
{
	for (int i = 0; i < RSIZEY; i++)
	{
		for (int j = 0; j < RSIZEX; j++)
		{
			areas[i][j] = Instantiate<Area>("123");
			areas[i][j].lock()->GetTransform()->SetParent(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j - RSIZEX / 2, i - RSIZEY / 2));
			areas[i][j].lock()->GetTransform()->RenderPriority = RenderPriorityType::Floor;
			if ((i + j) % 2)
				areas[i][j].lock()->GetTransform()->renderBox.setFillColor(Color::Magenta);
			else
				areas[i][j].lock()->GetTransform()->renderBox.setFillColor(Color::Black);
			areas[i][j].lock()->GetTransform()->SetSize(GetTransform()->GetAreaSize(), BoxType::RenderBox, FIX_ALL_RECT_POSITION);
		}
	}
}
void Room::SetObject()
{
	for (int i = 0; i < RSIZEY; i++)
	{
		for (int j = 0; j < RSIZEX; j++)
		{
			areas[i][j] = Instantiate<Area>("123");
			areas[i][j].lock()->GetTransform()->SetParent(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j - RSIZEX / 2, i - RSIZEY / 2));
			areas[i][j].lock()->GetTransform()->RenderPriority = RenderPriorityType::Floor;
			if ((i + j) % 2)
				areas[i][j].lock()->GetTransform()->renderBox.setFillColor(Color::Magenta);
			else
				areas[i][j].lock()->GetTransform()->renderBox.setFillColor(Color::Black);
			areas[i][j].lock()->GetTransform()->SetSize(GetTransform()->GetAreaSize(), BoxType::RenderBox, FIX_ALL_RECT_POSITION);
		}
	}
}
void Room::LoadallObject() {

}
void Room::Update() {
	if (WorldControl::isGamePlaying()&&
	WControl::getMainDungeon().Rooms[WControl::GetCurrentRoom().y][WControl::GetCurrentRoom().x].lock() == GetTransform()->wp.lock())
	{
		CheckCollisionInRoom();
	}
}
void Room::CheckCollisionInRoom() {
	CheckCollisionBetweenPlayerAndWall();
}
void Room::CheckCollisionBetweenPlayerAndWall() {
	static clock_t startTime(0);
	static clock_t delay=0.05*CLOCKS_PER_SEC;
	if (!Collision::isCollision(GetTransform()->renderBox, WControl::player().lock()->transform->renderBox) && clock() - startTime >= delay) {
		startTime = clock();
		Vector2f distance = WControl::player().lock()->transform->position - GetTransform()->position;
		int x = WControl::GetCurrentRoom().x, y = WControl::GetCurrentRoom().y;
		if (abs(distance.x) > abs(distance.y)) {
			if (distance.x >= 0) {
				if (x + 1 < 5) {
					WControl::SetCurrentRoom(Vector2i(++x, y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2i(0, RSIZEY / 2));
					printf("Right\n");
				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2i(RSIZEX, RSIZEY / 2));
				}
			}
			else {
				if (x-1>=0) {
					WControl::SetCurrentRoom(Vector2i(--x , y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2i(RSIZEX, RSIZEY / 2));
					printf("Left\n");

				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2i(0, RSIZEY / 2));
				}
			}
		}
		else {
			if (distance.y >= 0) {
				if (y + 1 < 5) {
					WControl::SetCurrentRoom(Vector2i(x, ++y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2i(RSIZEX / 2, 0));
					printf("Up\n");
				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2i(RSIZEX/2, RSIZEY ));
				}
			}
			else {
				if (y - 1 >= 0) {
					WControl::SetCurrentRoom(Vector2i(x, --y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom() , Vector2i(RSIZEX / 2, RSIZEY));
					printf("down\n");
				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2i(RSIZEX / 2, 0));
				}
			}
		}
		LoadNearbyRoom();
	}
}
void Room::LoadNearbyRoom() {
	int x= WControl::GetCurrentRoom().x, y = WControl::GetCurrentRoom().y;
	if (x+1<5&&!WControl::getMainDungeon().havePast[y][x]) {

	}
}
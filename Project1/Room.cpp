#include "Room.h"
#include "Collision.h"
#include "WorldControl.h"
#include "Dungeon.h"
#include <iostream>
#include <time.h>
#include <stdio.h>

Room::Room() {}
Room::Room(std::string s) :Tilemap(s) {}
void Room::SetRoom(const Vector2i& roomPosition) {
	this->roomPosition = roomPosition;
	SetFloor();
	
}
void Room::SetRoom1(RoomData roomData) {
	this->rooomData = roomData;
	for (size_t i = 0; i < roomData.objects.size(); i++)
	{
		for (size_t j = 0; j < roomData.objects[i].size(); j++)
		{
			switch (roomData.objects[i][j] / 10) {
			case 0:break;
			case 1:
			{	
				SpriteOffsetData spriteOffset(Vector2i(32, 23), Vector2i(123, 123), Vector2f(100, 40), Vector2f(0, 40), Vector2f(0, -5), float(0.8));
				Objects.push_back(Instantiate<Area>("Block"));
				Objects[Objects.size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[Objects.size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::ChargeSoul)]);
				Objects[Objects.size() - 1].lock()->GetTransform()->SetSpriteOffset(spriteOffset);
				Objects[Objects.size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case 2:
			{
				Vector2f v(-70,0);
				SpriteOffsetData spriteOffset(Vector2i(4, 25), Vector2i(182, 219), Vector2f(120, 50), Vector2f(0, 92), Vector2f(0, -34), float(0.7));
				Objects.push_back(Instantiate<Area>("Block"));
				Objects[Objects.size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[Objects.size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Bell)]);
				Objects[Objects.size() - 1].lock()->GetTransform()->SetSpriteOffset(spriteOffset);
				Objects[Objects.size() - 1].lock()->GetTransform()->SetSize(((Vector2f)spriteOffset.renderPixelSize + v)*spriteOffset.scale, PseudoRenderBox);
				Objects[Objects.size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case 3:
			{
				SpriteOffsetData spriteOffset(Vector2i(34, 29), Vector2i(125, 212), Vector2f(120, 60), Vector2f(0, 75), Vector2f(0, -30), float(0.70));
				Objects.push_back(Instantiate<Area>("Block"));
				Objects[Objects.size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[Objects.size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Hook)]);
				Objects[Objects.size() - 1].lock()->GetTransform()->SetSpriteOffset(spriteOffset);
				Objects[Objects.size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case 4:
			{
				SpriteOffsetData spriteOffset(Vector2i(1, 21), Vector2i(188, 177), Vector2f(100, 50), Vector2f(0, 70), Vector2f(0, -20), float(0.8));
				Objects.push_back(Instantiate<Area>("Block"));
				Objects[Objects.size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[Objects.size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Portal)]);
				Objects[Objects.size() - 1].lock()->GetTransform()->SetSpriteOffset(spriteOffset);
				Objects[Objects.size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case 5:
			{
				SpriteOffsetData spriteOffset(Vector2i(22, 9), Vector2i(154, 205), Vector2f(120, 40), Vector2f(0, 85), Vector2f(0, -20), float(0.7));
				Objects.push_back(Instantiate<Area>("Block"));
				Objects[Objects.size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[Objects.size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Strawberry)]);
				Objects[Objects.size() - 1].lock()->GetTransform()->SetSpriteOffset(spriteOffset);
				Objects[Objects.size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case 6:
			{
				SpriteOffsetData spriteOffset(Vector2i(0, 0), Vector2i(190, 140), Vector2f(190, 140), Vector2f(0, 0), Vector2f(0, 0), float(1));
				Objects.push_back(Instantiate<Area>("Block"));
				Objects[Objects.size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[Objects.size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::MovingPlatform)]);
				Objects[Objects.size() - 1].lock()->GetTransform()->SetSpriteOffset(spriteOffset);
				Objects[Objects.size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case 7:
			{
				SpriteOffsetData spriteOffset(Vector2i(10, 11), Vector2i(172, 147), Vector2f(155,40), Vector2f(-8, 60), Vector2f(5,-40), float(0.85));
				Objects.push_back(Instantiate<Area>("Block"));
				Objects[Objects.size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[Objects.size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Switch)]);
				Objects[Objects.size() - 1].lock()->GetTransform()->SetSpriteOffset(spriteOffset);
				Objects[Objects.size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			}
		}
	}
}
void Room::ResetRoom() {
	for (size_t i = 0; i < Objects.size(); i++)
	{
		type_index typeindex= Objects[i].lock()->GetTransform()->typeIndex;
		Destroy(Objects[i], typeindex);
	}
	Objects.clear();
}
void Room::SetFloor()
{
	for (int i = 0; i < RSIZEY; i++)
	{
		for (int j = 0; j < RSIZEX; j++)
		{
			areas[i][j] = Instantiate<Area>("123");
			if ((i + j) % 2)
				areas[i][j].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j+1, i+1 )
					, RenderPriorityType::Floor, Color::Magenta);
			else
				areas[i][j].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j+1, i+1)
					, RenderPriorityType::Floor, Color::Black);
		}
	}
}
void Room::SetObject()
{
}
void Room::Update() {
	if (WorldControl::isGamePlaying() && WControl::GetCurrentRoom() == roomPosition)
	{
		CheckCollisionInRoom();
	}
}
void Room::CheckCollisionInRoom() {
	CheckCollisionBetweenPlayerAndRoomEdge();
	CheckCollisionBetweenPlayerAndObject();
	CheckCollisionBetweenPlayerAndWall();
}
void Room::CheckCollisionBetweenPlayerAndWall() {
	for (size_t i = 0; i < Walls.size(); i++){
		Vector2f result;
		if (Collision::findShortestCollisionDistance(result, WControl::player().lock()->transform->hitBox, Walls[i].lock()->GetTransform()->renderBox)) {
			WControl::player().lock()->transform->Move(Vector2f(result.x / WControl::player().lock()->transform->scale.x, result.y / WControl::player().lock()->transform->scale.y));
		}
	}
}
void Room::CheckCollisionBetweenPlayerAndRoomEdge() {
	static clock_t startTime(0);
	static clock_t delay = 0.05 * CLOCKS_PER_SEC;
	if (!Collision::isCollision(GetTransform()->renderBox, WControl::player().lock()->transform->hitBox) && clock() - startTime >= delay) {
		startTime = clock();
		Vector2f distance = WControl::player().lock()->transform->position - MiddlePositionOfRoom();
		int x = roomPosition.x, y = roomPosition.y;
		if (abs(distance.x) > abs(distance.y)) {
			if (distance.x >= 0) {
				if (x + 1 < 5) {
					WControl::SetCurrentRoom(Vector2i(++x, y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2f(1,RSIZEY/2+0.5));
					printf("%d %d Right\n", roomPosition.x, roomPosition.y);
				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2f(RSIZEX, RSIZEY / 2 +0.5));
				}
			}
			else {
				if (x - 1 >= 0) {
					WControl::SetCurrentRoom(Vector2i(--x, y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2f(RSIZEX, RSIZEY / 2+0.5 ));
					printf("%d %d Left\n", roomPosition.x, roomPosition.y);
				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2f(1, RSIZEY / 2+0.5));
				}
			}
		}
		else {
			if (distance.y >= 0) {
				if (y + 1 < 5) {
					WControl::SetCurrentRoom(Vector2i(x, ++y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2f(RSIZEX / 2 + 0.5,1));
					printf("%d %d Down\n", roomPosition.x, roomPosition.y);
				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2f(RSIZEX / 2 + 0.5, RSIZEY));
				}
			}
			else {
				if (y - 1 >= 0) {
					WControl::SetCurrentRoom(Vector2i(x, --y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2f(RSIZEX / 2 + 0.5, RSIZEY));
					printf("%d %d Up\n", roomPosition.x, roomPosition.y);
				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoom(), Vector2f(RSIZEX / 2 + 0.5, 1));
				}
			}
		}
		WControl::getMainDungeon().havePast[y][x] = true;
		Room::UnLoadNearbyRoom();
		WControl::getMainDungeon().Rooms[y][x].lock()->LoadNearbyRoom();
		//WControl::view().setCenter(WControl::getMainDungeon().Rooms[y][x].lock()->GetTransform()->renderBox.getPosition());
	}
}
void Room::CheckCollisionBetweenPlayerAndObject() {
	for (size_t i = 0; i < Objects.size(); i++)
	{
		Vector2f result;
		if (Collision::findShortestCollisionDistance(result,WControl::player().lock()->transform->hitBox, Objects[i].lock()->GetTransform()->hitBox)) {
			/*printf("Collision ");
			if (result.x == 0) {
				if (result.y > 0) {
					printf("Up");
				}
				else {
					printf("Down");
				}
			}
			else if (result.y == 0) {
				if (result.x > 0) {
					printf("Left");
				}
				else {
					printf("Right");
				}
				
			}
			printf("\n");*/
			WControl::player().lock()->transform->Move(Vector2f(result.x / WControl::player().lock()->transform->scale.x, result.y / WControl::player().lock()->transform->scale.y) );
		}
	}
}
Vector2f Room::MiddlePositionOfRoom() {
	return GetTransform()->position + Multiple(GetTransform()->GetAreaSize(), Vector2f(RSIZEX / 2 + 0.5, RSIZEY / 2 + 0.5));
}
void Room::UnLoadNearbyRoom() {
	int x = roomPosition.x, y = roomPosition.y;
	if (x + 1 < 5 && !WControl::getMainDungeon().havePast[y][x + 1]) {
		if (WControl::getMainDungeon().bVerticleEdge[y][x + 1]) {
			WControl::getMainDungeon().Rooms[y][x + 1].lock()->ResetRoom();
		}
	}
	if (x - 1 >= 0 && !WControl::getMainDungeon().havePast[y][x - 1]) {
		if (WControl::getMainDungeon().bVerticleEdge[y][x]) {
			WControl::getMainDungeon().Rooms[y][x - 1].lock()->ResetRoom();
		}
	}
	if (y + 1 < 5 && !WControl::getMainDungeon().havePast[y + 1][x]) {
		if (WControl::getMainDungeon().bHorizonEdge[y + 1][x]) {
			WControl::getMainDungeon().Rooms[y + 1][x].lock()->ResetRoom();
		}
	}
	if (y - 1 >= 0 && !WControl::getMainDungeon().havePast[y - 1][x]) {
		if (WControl::getMainDungeon().bHorizonEdge[y][x]) {
			WControl::getMainDungeon().Rooms[y - 1][x].lock()->ResetRoom();
		}
	}
}
void Room::LoadNearbyRoom() {
	int x = roomPosition.x, y = roomPosition.y;
	if (x + 1 < 5 && !WControl::getMainDungeon().havePast[y][x + 1] && WControl::getMainDungeon().bVerticleEdge[y][x + 1]) {
		WControl::getMainDungeon().Rooms[y][x + 1].lock()->SetRoom1(WControl::usedRoomPrefabs()[GetRoomType(Align::HoriZontal, Vector2i(x + 1, y))][0]);
	}
	if (x - 1 >= 0 && !WControl::getMainDungeon().havePast[y][x - 1] && WControl::getMainDungeon().bVerticleEdge[y][x]) {
		WControl::getMainDungeon().Rooms[y][x - 1].lock()->SetRoom1(WControl::usedRoomPrefabs()[GetRoomType(Align::HoriZontal, Vector2i(x - 1, y))][0]);
	}
	if (y + 1 < 5 && !WControl::getMainDungeon().havePast[y + 1][x] && WControl::getMainDungeon().bHorizonEdge[y + 1][x]) {
		WControl::getMainDungeon().Rooms[y + 1][x].lock()->SetRoom1(WControl::usedRoomPrefabs()[GetRoomType(Align::Verticle, Vector2i(x, y + 1))][0]);
	}
	if (y - 1 >= 0 && !WControl::getMainDungeon().havePast[y - 1][x] && WControl::getMainDungeon().bHorizonEdge[y][x]) {
		WControl::getMainDungeon().Rooms[y - 1][x].lock()->SetRoom1(WControl::usedRoomPrefabs()[GetRoomType(Align::Verticle, Vector2i(x, y - 1))][0]);
	}
}


//static
void Room::getSumOfAlignEdge(int& xSum, int& ySum, const int& x, const int& y) {
	xSum = (int)WControl::getMainDungeon().bVerticleEdge[y][x] + WControl::getMainDungeon().bVerticleEdge[y][x + 1];
	ySum = (int)WControl::getMainDungeon().bHorizonEdge[y][x] + WControl::getMainDungeon().bHorizonEdge[y + 1][x];
}
RoomType Room::GetRoomType(const Align& align, const int& xSum, const int& ySum) {
	switch (ySum * 3 + xSum)
	{
	case 0:return RoomType::Type00;
	case 1:return RoomType::Type01;
	case 2:return RoomType::Type02;
	case 3:return RoomType::Type10;
	case 4:if (align == Align::Verticle) return RoomType::Type11_Verticle; else return RoomType::Type11_Horizon;
	case 5:if (align == Align::Verticle) return RoomType::Type12_Verticle; else return RoomType::Type12_Horizon;
	case 6:return RoomType::Type20;
	case 7:if (align == Align::Verticle) return RoomType::Type21_Verticle; else return RoomType::Type21_Horizon;
	case 8:if (align == Align::Verticle) return RoomType::Type22_Verticle; else return RoomType::Type22_Horizon;
	}
}
RoomType Room::GetRoomType(const Align& align, Vector2i roomPosition) {
	int xSum, ySum;
	getSumOfAlignEdge(xSum, ySum, roomPosition.x, roomPosition.y);
	return GetRoomType(align, xSum, ySum);
}
static std::string ObjectTypeString[30];
void Room::SetObjectTypeString() {
	ObjectTypeString[(int)ObjectType::Bell] = "Bell";
	ObjectTypeString[ObjectType::ChargeSoul] = "ChargeSoul";
	ObjectTypeString[ObjectType::Gate] = "Gate";
	ObjectTypeString[ObjectType::Hook] = "Hook";
	ObjectTypeString[ObjectType::Laser] = "Laser";
	ObjectTypeString[ObjectType::MovingPlatform] = "MovingPlatform";
	ObjectTypeString[ObjectType::PlacingSwitch] = "PlacingSwitch";
	ObjectTypeString[ObjectType::Portal] = "Portal";
	ObjectTypeString[ObjectType::Stone] = "Stone";
	ObjectTypeString[ObjectType::Strawberry] = "Strawberry";
	ObjectTypeString[ObjectType::Switch] = "Switch";
	ObjectTypeString[ObjectType::Null] = "";
}
std::string Room::ObjectTypeToString(const ObjectType& objectType) {
	return ObjectTypeString[objectType];
}
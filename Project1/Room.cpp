#include "Room.h"
#include "Collision.h"
#include "WorldControl.h"
#include "Dungeon.h"

#include "StrawberryClass.h"
#include "ChargeSoulClass.h"
#include "PortalClass.h"
#include "BellClass.h"
#include "NormalBlockClass.h"
#include "DeleteBlockClass.h"

#include <iostream>
#include <time.h>
#include <stdio.h>

vector<ObjectType> _walkableObjectTypes({ Strawberry, Portal ,SignalBlock });
vector<ObjectType> _unwalkableObjectTypes({ Bell,ChargeSoul,Hook,Switch,NormalBlock,DeleteBlock,MoveableBlock });
vector<ObjectType> _meleeAttackableObjectTypes({ ChargeSoul ,Bell });
vector<ObjectType> _hookAbleableObjectTypes({ Hook });
vector<ObjectType> _hookingCanclerObjectTypes({ Hook,Bell,Portal,ChargeSoul ,NormalBlock,DeleteBlock,MoveableBlock });
vector<ObjectType> _knifeInteractable({ Portal,Bell,DeleteBlock,NormalBlock,SignalBlock });

Room::Room() {}
Room::Room(std::string s) :Tilemap(s) {}

const vector<ObjectType>& Room::WalkableObjectTypes() { return _walkableObjectTypes; }
const vector<ObjectType>& Room::UnwalkableObjectTypes() { return _unwalkableObjectTypes; }
const vector<ObjectType>& Room::MeleeAttackableObjectTypes() { return _meleeAttackableObjectTypes; }
const vector<ObjectType>& Room::HookAbleableObjectTypes() { return _hookAbleableObjectTypes; }
const vector<ObjectType>& Room::HookingCanclerObjectTypes() { return _hookingCanclerObjectTypes; }
const vector<ObjectType>& Room::KnifeInteractableObjectTypes() { return _knifeInteractable; }

void Room::SetRoom(const Vector2i& roomPosition) {
	this->roomPosition = roomPosition;
}
void Room::SetRoomSeed(const RoomData& roomData,const bool& isFlipX,const bool& isFlipY)
{
	originalRoomData = roomData;
	if (isFlipX) {
		for (auto& wp: originalRoomData.floor) {
			std::reverse(wp.begin(),wp.end());
		}
		for (auto& wp: originalRoomData.objects) {
			std::reverse(wp.begin(),wp.end());
		}
		for (auto& wp: originalRoomData.track) {
			std::reverse(wp.begin(), wp.end());
		}
	}
	if (isFlipY) {
		std::reverse(originalRoomData.floor.begin(), originalRoomData.floor.end());
		std::reverse(originalRoomData.objects.begin(), originalRoomData.objects.end());
		std::reverse(originalRoomData.track.begin(), originalRoomData.track.end());
	}
	this->roomData = originalRoomData;
	ResetRoom();
	SetFloor();
	SetAllObjectsInRoom();
}
void Room::SetAllObjectsInRoom() {
	for (size_t i = 0; i < roomData.objects.size(); i++)
	{
		for (size_t j = 0; j < roomData.objects[i].size(); j++)
		{
			switch (roomData.objects[i][j] / 10) {
			case ObjectType::Null:break;
			case  ObjectType::ChargeSoul:
				InstantChargeSoul(Vector2i(j+1,i+1));
				break;
			case  Bell:
				InstantBell(Vector2i(j + 1, i + 1));	
				break;
			case  Hook:
				InstantHook(Vector2i(j + 1, i + 1));
				break;
			case  Portal:
				InstantPortal(Vector2i(j + 1, i + 1));
				break;
			case  Strawberry:
				InstantStrawberry(Vector2i(j + 1, i + 1));
				break;
			case  MovingPlatform:
				InstantMovingPlatform(Vector2i(j + 1, i + 1));
				break;
			case  Switch:
				InstantSwitch(Vector2i(j + 1, i + 1));
				break;
			case  ObjectType::PlacingSwitch:
				InstantPlacingSwitch(Vector2i(j + 1, i + 1));
				break;
			case  ObjectType::NormalBlock:
				InstantNormalBlock(Vector2i(j + 1, i + 1));
				break;
			case  ObjectType::DeleteBlock:
				InstantDeleteBlock(Vector2i(j + 1, i + 1));
				break;
			case  ObjectType::SignalBlock:
				InstantSignalBlock(Vector2i(j + 1, i + 1));
				break;
			case  ObjectType::MoveableBlock:
				InstantMoveableBlock(Vector2i(j + 1, i + 1));
				break;
			}
		}
	}
}
void Room::ResetRoom() {
	for (auto& Object : Objects) {
		for (weak_ptr<Area> wp : Object.second)
		{
			if (!wp.expired()) {
				type_index typeindex = wp.lock()->GetTransform()->typeIndex;
				Destroy(wp, typeindex);
			}
		}
		Object.second.clear();
	}
	for (auto& areaRow : areas) {
		for (auto& area : areaRow) {
			if (!area.expired()) {
				auto wp = area.lock()->GetTransform()->wp;
				auto typeIndex = area.lock()->GetTransform()->typeIndex;
				Destroy(wp, typeIndex);
			}
		}
	}
	cliffs.clear();
}
void Room::RestartRoom()
{
	ResetRoom();
	SetRoomSeed(originalRoomData,false,false);
	WControl::player().lock()->transform->position = startRoomPosition;
}

void Room::SetFloor()
{
	for (int i = 0; i < RSIZEY; i++)
	{
		for (int j = 0; j < RSIZEX; j++)
		{
			if (roomData.floor[i][j] == false) {
				areas[i][j] = Instantiate<Area>("Floor");
				if ((i + j) % 2)
					areas[i][j].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1) 
						, RenderPriorityType::Floor, Color::Magenta);
				else
					areas[i][j].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1) 
						, RenderPriorityType::Floor, Color::Black);
			}
			else {
				areas[i][j] = Instantiate<Area>("Floor");
				cliffs.push_back(areas[i][j]);
				areas[i][j].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j+1, i + 1) 
					, RenderPriorityType::Floor, Color::Blue);
			}
		}
	}
}

void Room::Update() {
	CheckCollisionInRoom();
}

void Room::DestroyAllEdge()
{
	for (auto& wall : Walls) {
		for (auto wp : wall) {
			weak_ptr<GameSprite> wp2 = wp.lock()->transform->wp;
			type_index typeI = wp.lock()->transform->typeIndex;
			Destroy(wp2, typeI);
		}
		wall.clear();
	}
}
void Room::DestroyAllObjects()
{
	for (auto& ObjectsByType : Objects) {
		for (auto object : ObjectsByType.second)
		{
			weak_ptr<GameSprite> wp = object.lock()->transform->wp;
			type_index typeI = object.lock()->transform->typeIndex;
			Destroy(wp, typeI);
		}
		ObjectsByType.second.clear();
	}
}

void Room::CheckCollisionInRoom() {
	WControl::player().lock()->lastFrameHitBox = WControl::player().lock()->transform->hitBox;
	CheckCollisionBetweenPlayerAndCliff();
	CheckCollisionBetweenPlayerAndRoomEdge();
	CheckCollisionBetweenPlayerAndObject();
	CheckCollisionBetweenPlayerAndWall();
	CheckCollisionOfKnife();
	if (WControl::player().lock()->isHooking)
		CheckCollisionBetweenPlayerAndHookingCancler();
	
	
}

void Room::CheckCollisionBetweenPlayerAndWall() {
	for (int j = 0; j < 4; j++) {
		for (size_t i = 0; i < Walls[j].size(); i++) {
			Vector2f result;
			if (Collision::findShortestCollisionDistance(result, WControl::player().lock()->transform->hitBox, Walls[j][i].lock()->GetTransform()->renderBox)) {
				WControl::player().lock()->lastFrameHitBox.move(result);
				WControl::player().lock()->transform->Move(Vector2f(result.x, result.y));
			}
		}
	}
}
void Room::CheckCollisionBetweenPlayerAndRoomEdge() {
	
	static clock_t startTime(0);
	static clock_t delay = 0.05 * CLOCKS_PER_SEC;
	if (!Collision::isCollision(GetTransform()->renderBox, WControl::player().lock()->transform->hitBox) && clock() - startTime >= delay) {
		//RestartRoom();
		startTime = clock();
		Vector2f distance = WControl::player().lock()->transform->position - MiddlePositionOfRoom();
		int x = roomPosition.x, y = roomPosition.y;
		if (abs(distance.x) > abs(distance.y)) {
			if (distance.x >= 0) {
				if (x + 1 < 5) {
					WControl::SetCurrentRoomPositon(Vector2i(++x, y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(1, RSIZEY / 2 ));
					printf("%d %d Right\n", roomPosition.x, roomPosition.y);
				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(RSIZEX, RSIZEY / 2 + 0.5));
				}
			}
			else {
				if (x - 1 >= 0) {
					WControl::SetCurrentRoomPositon(Vector2i(--x, y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(RSIZEX, RSIZEY / 2 ));
					printf("%d %d Left\n", roomPosition.x, roomPosition.y);
				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(1, RSIZEY / 2 + 0.5));
				}
			}
		}
		else {
			if (distance.y >= 0) {
				if (y + 1 < 5) {
					WControl::SetCurrentRoomPositon(Vector2i(x, ++y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(RSIZEX / 2+0.5 , 0.5));
					printf("%d %d Down\n", roomPosition.x, roomPosition.y);
				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(RSIZEX / 2 + 0.5, RSIZEY));
				}
			}
			else {
				if (y - 1 >= 0) {
					WControl::SetCurrentRoomPositon(Vector2i(x, --y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(RSIZEX / 2 +0.5, RSIZEY-0.5));
					printf("%d %d Up\n", roomPosition.x, roomPosition.y);
				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(RSIZEX / 2 + 0.5, 1));
				}
			}
		}
		if (!WControl::getMainDungeon().havePast[y][x]) {
			WControl::getMainDungeon().havePast[y][x] = true;
			WControl::GetCurrentRoom().lock()->startRoomPosition = WControl::player().lock()->transform->position;
		}
		Room::UnLoadNearbyRoom();
		WControl::getMainDungeon().Rooms[y][x].lock()->LoadNearbyRoom();
		WControl::player().lock()->ResetSoul();
	}
}
void Room::CheckCollisionBetweenPlayerAndObject() {
	{
		for (int i = 0; i < WalkableObjectTypes().size(); i++) {
			ObjectType obj = WalkableObjectTypes()[i];
			vector<weak_ptr<Area> > v;
			for (size_t j = 0; j < Objects[obj].size(); j++)
			{
				if (!Objects[obj][j].expired()) {
					if (Collision::isCollision(WControl::player().lock()->transform->hitBox, Objects[obj][j].lock()->GetTransform()->hitBox)) {
						weak_ptr<Walkable> wp = dynamic_pointer_cast<Walkable>(Objects[obj][j].lock());
						if (!wp.expired()) {
							wp.lock()->WalkThroughActivate();
						}
					}
					v.push_back(Objects[obj][j]);
				}
			}
			Objects[obj] = v;
		}
	}
	if (!WControl::player().lock()->isHooking) {

		for (int i = 0; i < UnwalkableObjectTypes().size(); i++) {
			ObjectType obj = UnwalkableObjectTypes()[i];
			vector<weak_ptr<Area> > v;
			for (size_t j = 0; j < Objects[obj].size(); j++)
			{
				if (!Objects[obj][j].expired()) {
					Vector2f result;
					if (Collision::findShortestCollisionDistance(result, WControl::player().lock()->lastFrameHitBox, Objects[obj][j].lock()->GetTransform()->hitBox)) {
						WControl::player().lock()->lastFrameHitBox.move(result);
						WControl::player().lock()->transform->Move(Vector2f(result.x, result.y));
					}
					v.push_back(Objects[obj][j]);
				}
			}
			Objects[obj] = v;
		}
	}
}
void Room::CheckCollisionBetweenPlayerAndCliff() {
	WControl::player().lock()->lastFrameHitBox = WControl::player().lock()->transform->hitBox;
	if (!WControl::player().lock()->isHooking) {
		for (auto& cliff : cliffs) {
			if (!cliff.expired()) {
				Vector2f result;
				if (Collision::findShortestCollisionDistance(result, WControl::player().lock()->lastFrameHitBox, cliff.lock()->GetTransform()->pseudoRenderBox)) {
					Vector2f point = WControl::player().lock()->lastFrameHitBox.getPosition() - Vector2f(0, WControl::player().lock()->transform->hitBox.getSize().y / 2);
					WControl::player().lock()->lastFrameHitBox.move(result);
					WControl::player().lock()->transform->Move(Vector2f(result.x, result.y));
					if (Collision::isCollision(cliff.lock()->GetTransform()->pseudoRenderBox, point)) {
						RestartRoom();
					}
				}
			}
			else {
				printf("Cliff is Expire\n");
			}
		}
	}
}

void Room::CheckCollisionRingHitBoxAndMeleeAttackableObject(weak_ptr<GameSprite> wp) {
	weak_ptr<BellClass> bell = dynamic_pointer_cast<BellClass>(wp.lock());
	if (!bell.expired()) {
		std::set<GameTransform*> newSet;
		for (int i = 0; i < MeleeAttackableObjectTypes().size(); i++) {
			ObjectType obj = MeleeAttackableObjectTypes()[i];
			vector<weak_ptr<Area> > v;
			for (size_t j = 0; j < Objects[obj].size(); j++)
			{
				if (!Objects[obj][j].expired()) {
					if (Collision::isCollision(bell.lock()->ringArea.lock()->transform->hitBox, Objects[obj][j].lock()->GetTransform()->pseudoRenderBox)) {
						if (bell.lock()->lastFrameCollisionObjects.find(Objects[obj][j].lock()->GetTransform()) == bell.lock()->lastFrameCollisionObjects.end()) {
							dynamic_pointer_cast<MeleeAttackable>(Objects[obj][j].lock())->MeleeAttackActivate();
						}
						newSet.insert(Objects[obj][j].lock()->GetTransform());
					}
					v.push_back(Objects[obj][j]);
				}
			}
			Objects[obj] = v;
		}
		bell.lock()->lastFrameCollisionObjects = newSet;
	}
	else {
		printf("You can't check this collision as this is not BellClass\n");
	}
}

void Room::CheckCollisionBetweenAttackHitBoxAndObject() {
	for (int i = 0; i < MeleeAttackableObjectTypes().size(); i++) {
		ObjectType obj = MeleeAttackableObjectTypes()[i];
		vector<weak_ptr<Area> > v;
		for (size_t j = 0; j < Objects[obj].size(); j++)
		{
			if (!Objects[obj][j].expired()) {
				if (Collision::isCollision(WControl::player().lock()->meleeAttackHitbox.lock()->transform->hitBox, Objects[obj][j].lock()->GetTransform()->pseudoRenderBox)) {
					weak_ptr<MeleeAttackable> wp = dynamic_pointer_cast<MeleeAttackable>(Objects[obj][j].lock());
					if (!wp.expired()) {
						wp.lock()->MeleeAttackActivate();
					}
				}
				v.push_back(Objects[obj][j]);
			}
		}
		Objects[obj] = v;
	}
}

void Room::CheckNearestObjectHooking() {
	float nearestDistance = FLT_MAX;
	vector<RectangleShape> rects;
	for (int i = 0; i < HookAbleableObjectTypes().size(); i++) {
		ObjectType obj = HookAbleableObjectTypes()[i];
		vector<weak_ptr<Area> > v;
		for (size_t j = 0; j < Objects[obj].size(); j++)
		{
			if (!Objects[obj][j].expired()) {
				rects.push_back(Objects[obj][j].lock()->GetTransform()->pseudoRenderBox);
				v.push_back(Objects[obj][j]);
			}
		}
		Objects[obj] = v;
	}
	{
		queue<weak_ptr<Knife>> knifes = WControl::player().lock()->knifes;
		queue<weak_ptr<Knife>> newKnifes;
		while (!knifes.empty())
		{
			weak_ptr<Knife> knife = knifes.front();
			knifes.pop();
			if (!knife.expired()) {
				newKnifes.push(knife);
				if(knife.lock()->GetIsStop())
					rects.push_back(knife.lock()->transform->pseudoRenderBox);
			}
		}
		WControl::player().lock()->knifes = newKnifes;
	}
	Vector2f result = WControl::player().lock()->GetRealThrowingPosition();
	if (!Collision::findShortestCollisionOfPointAtDirection(result, result, rects, WControl::player().lock()->HoldingDirection)) {
		switch (WControl::player().lock()->HoldingDirection)
		{
		case Right:
			result.x = WControl::MainTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(RSIZEX + 0.5, RSIZEY + 0.5)).x;
			break;
		case Left:
			result.x = WControl::MainTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(0.5, 0.5)).x;
			break;
		case Up:
			result.y = WControl::MainTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(0.5, 0.5)).y;
			break;
		case Down:
			result.y = WControl::MainTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(RSIZEX + 0.5, RSIZEY + 0.5)).y;
			break;
		}
		WControl::player().lock()->canHook = false;
	}
	else {
		WControl::player().lock()->canHook = true;
		WControl::player().lock()->EndPosition() = result;
		WControl::player().lock()->StartPosition() = WControl::player().lock()->GetRealThrowingPosition();
	}
	Vector2f distanceVec = result - WControl::player().lock()->GetRealThrowingPosition();
	float distance = sqrt(pow(distanceVec.x, 2) + pow(distanceVec.y, 2));
	WControl::player().lock()->hookGuideLine.setSize(Vector2f(distance, GUIDELINE_THICKNESS));
	WControl::player().lock()->hookGuideLine.setOrigin(Multiple(WControl::player().lock()->hookGuideLine.getSize(), Vector2f(0.5, 0.5)));
	WControl::player().lock()->hookGuideLine.setPosition(Multiple(result + WControl::player().lock()->GetRealThrowingPosition(), Vector2f(0.5, 0.5)));
}
void Room::CheckCollisionBetweenPlayerAndHookingCancler() {
	for (int i = 0; i < HookingCanclerObjectTypes().size(); i++) {
		ObjectType obj = HookingCanclerObjectTypes()[i];
		vector<weak_ptr<Area> > v;
		for (size_t j = 0; j < Objects[obj].size(); j++)
		{
			if (!Objects[obj][j].expired()) {
				if (Collision::isCollision(WControl::player().lock()->transform->hitBox, Objects[obj][j].lock()->GetTransform()->hitBox)) {
					WControl::player().lock()->CancleHooking();
				}
				v.push_back(Objects[obj][j]);
			}
		}
		Objects[obj] = v;
	}
}

void Room::CheckCollisionOfKnife() {

	queue<weak_ptr<Knife>> knifes = WControl::player().lock()->knifes;
	queue<weak_ptr<Knife>> newKnifes;
	while (!knifes.empty())
	{
		weak_ptr<Knife> knife = knifes.front();
		knifes.pop();
		if (!knife.expired()) {
			Direction direction = knife.lock()->GetDirection();
			newKnifes.push(knife);
			for (ObjectType obj : KnifeInteractableObjectTypes()) {
				vector<weak_ptr<Area> > v;
				for (auto& object : Objects[obj])
				{
					if (!object.expired()) {
						if (!knife.expired() && !knife.lock()->GetIsStop() && Collision::isCollision(knife.lock()->transform->hitBox, object.lock()->transform->hitBox)) {
							weak_ptr<KnifeInteractable> wp = dynamic_pointer_cast<KnifeInteractable>(object.lock());
							if (!wp.expired()) {
								wp.lock()->interacting(knife);
							}
						}
						v.push_back(object);
					}
				}
				Objects[obj] = v;
			}

			for (auto& wall : Walls[direction]) {
				if (!knife.expired() && !knife.lock()->GetIsStop() && Collision::isCollision(knife.lock()->transform->hitBox, wall.lock()->GetTransform()->renderBox)) {
					auto wp = knife.lock()->transform->wp;
					auto index = knife.lock()->transform->typeIndex;
					Destroy(wp, index);
				}
			}
		}
	}
	WControl::player().lock()->knifes = newKnifes;
}

const Vector2f& Room::MiddlePositionOfRoom() {
	return GetTransform()->position  + Multiple(Tile::GetAreaSize(), Vector2f(RSIZEX / 2 + 0.5, RSIZEY / 2 + 0.5));
}
const Vector2f& Room::TopLeftPositionOfRoom() {
	return GetTransform()->position + Multiple(Tile::GetAreaSize(), Vector2f(-0.5,-0.5));
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
		bool flipX = false, flipY = false;
		RoomType roomType = GetRoomType(Direction::Left, Vector2i(x + 1, y),&flipX,&flipY);
		WControl::getMainDungeon().Rooms[y][x + 1].lock()->SetRoomSeed(WControl::usedRoomPrefabs()[roomType][0],flipX,flipY);
	}
	if (x - 1 >= 0 && !WControl::getMainDungeon().havePast[y][x - 1] && WControl::getMainDungeon().bVerticleEdge[y][x]) {
		bool flipX = false, flipY = false;
		RoomType roomType = GetRoomType(Direction::Right, Vector2i(x-1, y), &flipX, &flipY);
		WControl::getMainDungeon().Rooms[y][x - 1].lock()->SetRoomSeed(WControl::usedRoomPrefabs()[roomType][0], flipX, flipY);
	}
	if (y + 1 < 5 && !WControl::getMainDungeon().havePast[y + 1][x] && WControl::getMainDungeon().bHorizonEdge[y + 1][x]) {
		bool flipX = false, flipY = false;
		RoomType roomType = GetRoomType(Direction::Up, Vector2i(x , y+1), &flipX, &flipY);
		WControl::getMainDungeon().Rooms[y+1][x].lock()->SetRoomSeed(WControl::usedRoomPrefabs()[roomType][0], flipX, flipY);
	}
	if (y - 1 >= 0 && !WControl::getMainDungeon().havePast[y - 1][x] && WControl::getMainDungeon().bHorizonEdge[y][x]) {
		bool flipX = false, flipY = false;
		RoomType roomType = GetRoomType(Direction::Down, Vector2i(x, y-1), &flipX, &flipY);
		WControl::getMainDungeon().Rooms[y-1][x].lock()->SetRoomSeed(WControl::usedRoomPrefabs()[roomType][0], flipX, flipY);
	}
}




//static
void Room::getSumOfAlignEdge(int& xSum, int& ySum, const int& x, const int& y) {
	xSum = (int)WControl::getMainDungeon().bVerticleEdge[y][x] + WControl::getMainDungeon().bVerticleEdge[y][x + 1];
	ySum = (int)WControl::getMainDungeon().bHorizonEdge[y][x] + WControl::getMainDungeon().bHorizonEdge[y + 1][x];
}

RoomType Room::GetRoomType(const Direction& direction, const int& xSum, const int& ySum) {
	switch (ySum * 3 + xSum)
	{
	case 0:return RoomType::Type00;
	case 1:return RoomType::Type01;
	case 2:return RoomType::Type02;
	case 3:return RoomType::Type10;
	case 4:if (direction < 2) return RoomType::Type11_Verticle; else return RoomType::Type11_Horizon;
	case 5:if (direction < 2) return RoomType::Type12_Verticle; else return RoomType::Type12_Horizon;
	case 6:return RoomType::Type20;
	case 7:if (direction < 2) return RoomType::Type21_Verticle; else return RoomType::Type21_Horizon;
	case 8:if (direction < 2) return RoomType::Type22_Verticle; else return RoomType::Type22_Horizon;
	}
}
RoomType Room::GetRoomType(const Direction& direction, Vector2i roomPosition,bool* FlipX,bool* FlipY) {
	bool bUp = WControl::getMainDungeon().bHorizonEdge[roomPosition.y][roomPosition.x],
		bDown = WControl::getMainDungeon().bHorizonEdge[roomPosition.y + 1][roomPosition.x],
		bLeft = WControl::getMainDungeon().bVerticleEdge[roomPosition.y][roomPosition.x],
		bRight = WControl::getMainDungeon().bVerticleEdge[roomPosition.y][roomPosition.x + 1];
	*FlipY = (direction == Down||(!bUp && bDown)) ? true : false;
	*FlipX = (direction == Right || (!bLeft && bRight)) ? true : false;
	return GetRoomType(direction, (int)bLeft+bRight, (int)bUp + bDown );
}
static std::string ObjectTypeString[30];
void Room::SetObjectTypeString() {
	ObjectTypeString[(int)ObjectType::Bell] = "Bell";
	ObjectTypeString[ObjectType::ChargeSoul] = "ChargeSoul";
	ObjectTypeString[ObjectType::Hook] = "Hook";
	ObjectTypeString[ObjectType::Laser] = "Laser";
	ObjectTypeString[ObjectType::MovingPlatform] = "MovingPlatform";
	ObjectTypeString[ObjectType::PlacingSwitch] = "PlacingSwitch";
	ObjectTypeString[ObjectType::Portal] = "Portal";
	ObjectTypeString[ObjectType::NormalBlock] = "NormalBlock";
	ObjectTypeString[ObjectType::DeleteBlock] = "DeleteBlock";
	ObjectTypeString[ObjectType::SignalBlock] = "SignalBlock";
	ObjectTypeString[ObjectType::MoveableBlock] = "MoveableBlock";
	ObjectTypeString[ObjectType::Strawberry] = "Strawberry";
	ObjectTypeString[ObjectType::Switch] = "Switch";
	ObjectTypeString[ObjectType::Null] = "";
}
std::string Room::ObjectTypeToString(const ObjectType& objectType) {
	return ObjectTypeString[objectType];
}

void Room::InstantChargeSoul(Vector2i pos) {
	SpriteOffsetData spriteOffset(Vector2i(32, 23), Vector2i(123, 123), Vector2f(60, 40), Vector2f(0, 40), Vector2f(0, -5), float(0.8));
	auto wp = Instantiate<ChargeSoulClass>("ChargeSoul");
	Objects[ChargeSoul].push_back(wp);
	wp.lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(pos.x, pos.y) 
		, RenderPriorityType::PlayerAndObject);
	wp.lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::ChargeSoul)]);
	wp.lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
	wp.lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
	Space[pos.y - 1][pos.x - 1]=wp;
}
void Room::InstantBell(Vector2i pos) {
	Vector2f v(-70, 0);
	SpriteOffsetData spriteOffset(Vector2i(4, 25), Vector2i(182, 219), Vector2f(120, 90), Vector2f(0, 64), Vector2f(0, -35), float(0.75));
	auto wp = Instantiate<BellClass>("Bell");
	Objects[Bell].push_back(wp);
	wp.lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), pos
		, RenderPriorityType::PlayerAndObject);
	wp.lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Bell)]);
	wp.lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
	wp.lock()->GetTransform()->SetSize(((Vector2f)spriteOffset.renderPixelSize + v) * spriteOffset.scale, PseudoRenderBox);
	wp.lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
	Space[pos.y - 1][pos.x - 1] = wp;
}
void Room::InstantHook(Vector2i pos) {
	SpriteOffsetData spriteOffset(Vector2i(34, 29), Vector2i(125, 212), Vector2f(70, 70), Vector2f(0, 70), Vector2f(0, -40), float(0.80));
	auto wp = Instantiate<Area>("Hook");
	Objects[Hook].push_back(wp);
	wp.lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), pos
		, RenderPriorityType::PlayerAndObject);
	wp.lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Hook)]);
	wp.lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
	wp.lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
	Space[pos.y - 1][pos.x - 1] = wp;
}
void Room::InstantPortal(Vector2i pos) {
	SpriteOffsetData spriteOffset(Vector2i(1, 21), Vector2i(188, 177), Vector2f(150, 80), Vector2f(0, 38), Vector2f(0, -20), float(0.85));
	auto wp = Instantiate<PortalClass>("Portal");
	Objects[Portal].push_back(wp);
	wp.lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), pos
		, RenderPriorityType::PlayerAndObject);
	wp.lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Portal)]);
	wp.lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
	wp.lock()->GetTransform()->SetSize(Objects[Portal][Objects[Portal].size() - 1].lock()->GetTransform()->pseudoRenderBox.getSize() - Vector2f(15, 15), PseudoRenderBox);
	wp.lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
	if (Portals[roomData.objects[pos.y-1][pos.x-1] % 10].expired())
		Portals[roomData.objects[pos.y-1][pos.x-1] % 10] = dynamic_pointer_cast<PortalClass>(Objects[Portal][Objects[Portal].size() - 1].lock());
	else {
		weak_ptr<PortalClass> wp = dynamic_pointer_cast<PortalClass>(Objects[Portal][Objects[Portal].size() - 1].lock());
		Portals[roomData.objects[pos.y-1][pos.x-1] % 10].lock()->Linking(wp);
		wp.lock()->Linking(Portals[roomData.objects[pos.y-1][pos.x-1] % 10]);
	}
	Space[pos.y - 1][pos.x - 1] = wp;
}
void Room::InstantStrawberry(Vector2i pos) {
	SpriteOffsetData spriteOffset(Vector2i(22, 9), Vector2i(154, 205), Vector2f(120, 60), Vector2f(0, 70), Vector2f(0, -32), float(0.75));
	auto wp = Instantiate<StrawberryClass>("Strawberry");
	Objects[Strawberry].push_back(wp);
	wp.lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), pos
		, RenderPriorityType::PlayerAndObject);
	wp.lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Strawberry)]);
	wp.lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
	wp.lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
	Space[pos.y - 1][pos.x - 1] = wp;
}
void Room::InstantMovingPlatform(Vector2i pos) {
	SpriteOffsetData spriteOffset(Vector2i(0, 0), Vector2i(190, 140), Vector2f(190, 140), Vector2f(0, 0), Vector2f(0, 0), float(1));
	auto wp = Instantiate<Area>("Block");
	Objects[MovingPlatform].push_back(wp);
	wp.lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), pos
		, RenderPriorityType::PlayerAndObject);
	wp.lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::MovingPlatform)]);
	wp.lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
	wp.lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
	Space[pos.y - 1][pos.x - 1] = wp;
}
void Room::InstantSwitch(Vector2i pos) {
	SpriteOffsetData spriteOffset(Vector2i(10, 11), Vector2i(172, 147), Vector2f(155, 40), Vector2f(-8, 60), Vector2f(5, -40), float(0.85));
	auto wp = Instantiate<Area>("Block");
	Objects[Switch].push_back(wp);
	wp.lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), pos
		, RenderPriorityType::PlayerAndObject);
	wp.lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Switch)]);
	wp.lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
	wp.lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
	Space[pos.y - 1][pos.x - 1] = wp;
}
void Room::InstantNormalBlock(Vector2i pos) {
	SpriteOffsetData spriteOffset(Vector2i(0, 0), Vector2i(150, 250), Vector2f(150, 140), Vector2f(0, 55), Vector2f(0, -55), float(1));
	auto wp = Instantiate<NormalBlockClass>("NormalBlock");
	Objects[NormalBlock].push_back(wp);
	wp.lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), pos
		, RenderPriorityType::PlayerAndObject);
	wp.lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::NormalBlock)]);
	wp.lock()->GetTransform()->SetAllSpriteOffset(spriteOffset, Vector2f(190. / 140, 1));
	wp.lock()->GetTransform()->SetSize(Vector2f(190, 140), PseudoRenderBox);
	wp.lock()->GetTransform()->MoveOffset(Vector2f(0, 55), PseudoRenderBox);
	wp.lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
	Space[pos.y - 1][pos.x - 1] = wp;
}
void Room::InstantDeleteBlock(Vector2i pos) {
	SpriteOffsetData spriteOffset(Vector2i(0, 0), Vector2i(150, 250), Vector2f(150, 140), Vector2f(0, 55), Vector2f(0, -55), float(1));
	auto wp = Instantiate<DeleteBlockClass>("DeleteBlock");
	Objects[DeleteBlock].push_back(wp);
	wp.lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), pos
		, RenderPriorityType::PlayerAndObject);
	wp.lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::DeleteBlock)]);
	wp.lock()->GetTransform()->SetAllSpriteOffset(spriteOffset, Vector2f(190. / 140, 1));
	wp.lock()->GetTransform()->SetSize(Vector2f(190, 140), PseudoRenderBox);
	wp.lock()->GetTransform()->MoveOffset(Vector2f(0, 55), PseudoRenderBox);
	wp.lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
	Space[pos.y - 1][pos.x - 1] = wp;
}
void Room::InstantSignalBlock(Vector2i pos) {
	SpriteOffsetData spriteOffset(Vector2i(0, 0), Vector2i(150, 250), Vector2f(150, 140), Vector2f(0, 55), Vector2f(0, -55), float(1));
	auto wp=Instantiate<NormalBlockClass>("SignalBlock");
	Objects[NormalBlock].push_back(wp);
	wp.lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()),pos
		, RenderPriorityType::PlayerAndObject);
	wp.lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::SignalBlock)]);
	wp.lock()->GetTransform()->SetAllSpriteOffset(spriteOffset, Vector2f(190. / 140, 1));
	wp.lock()->GetTransform()->SetSize(Vector2f(190, 140), PseudoRenderBox);
	wp.lock()->GetTransform()->MoveOffset(Vector2f(0, 55), PseudoRenderBox);
	wp.lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
	Space[pos.y - 1][pos.x - 1] = wp;
}
void Room::InstantMoveableBlock(Vector2i pos) {
	SpriteOffsetData spriteOffset(Vector2i(0, 0), Vector2i(150, 250), Vector2f(150, 140), Vector2f(0, 55), Vector2f(0, -55), float(1));
	auto wp = Instantiate<NormalBlockClass>("NormalBlock");
	Objects[NormalBlock].push_back(wp);
	wp.lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), pos
		, RenderPriorityType::PlayerAndObject);
	wp.lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::MoveableBlock)]);
	wp.lock()->GetTransform()->SetAllSpriteOffset(spriteOffset, Vector2f(190. / 140, 1));
	wp.lock()->GetTransform()->SetSize(Vector2f(190, 140), PseudoRenderBox);
	wp.lock()->GetTransform()->MoveOffset(Vector2f(0, 55), PseudoRenderBox);
	wp.lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
	Space[pos.y - 1][pos.x - 1] = wp;
}
void Room::InstantPlacingSwitch(Vector2i pos) {}
void Room::InstantLaser(Vector2i pos) {}

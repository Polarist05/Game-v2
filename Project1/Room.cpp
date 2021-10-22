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

vector<ObjectType> _walkableObjectTypes({ Strawberry, Portal ,SignalBlock});
vector<ObjectType> _unwalkableObjectTypes({ Bell,ChargeSoul,Hook,Switch,NormalBlock,DeleteBlock,MoveableBlock });
vector<ObjectType> _meleeAttackableObjectTypes({ ChargeSoul ,Bell });
vector<ObjectType> _hookAbleableObjectTypes({ Hook });
vector<ObjectType> _hookingCanclerObjectTypes({ Hook,Bell,Portal,ChargeSoul ,NormalBlock,DeleteBlock,MoveableBlock});
vector<ObjectType> _knifeInteractable({Portal,Bell,DeleteBlock,NormalBlock,SignalBlock});

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
	SetFloor();

}
void Room::SetAllObjectsInRoom(RoomData roomData) {
	this->rooomData = roomData;
	vector<weak_ptr<PortalClass>> Portals(10, weak_ptr<PortalClass>());
	for (size_t i = 0; i < roomData.objects.size(); i++)
	{
		for (size_t j = 0; j < roomData.objects[i].size(); j++)
		{
			switch (roomData.objects[i][j] / 10) {
			case ObjectType::Null:break;
			case  ObjectType::ChargeSoul:
			{
				SpriteOffsetData spriteOffset(Vector2i(32, 23), Vector2i(123, 123), Vector2f(60, 40), Vector2f(0, 40), Vector2f(0, -5), float(0.8));
				Objects[ChargeSoul].push_back(Instantiate<ChargeSoulClass>("ChargeSoul"));
				Objects[ChargeSoul][Objects[ChargeSoul].size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[ChargeSoul][Objects[ChargeSoul].size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::ChargeSoul)]);
				Objects[ChargeSoul][Objects[ChargeSoul].size() - 1].lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
				Objects[ChargeSoul][Objects[ChargeSoul].size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case  Bell:
			{
				Vector2f v(-70, 0);
				SpriteOffsetData spriteOffset(Vector2i(4, 25), Vector2i(182, 219), Vector2f(120, 90), Vector2f(0, 64), Vector2f(0, -35), float(0.75));
				Objects[Bell].push_back(Instantiate<BellClass>("Bell"));
				Objects[Bell][Objects[Bell].size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[Bell][Objects[Bell].size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Bell)]);
				Objects[Bell][Objects[Bell].size() - 1].lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
				Objects[Bell][Objects[Bell].size() - 1].lock()->GetTransform()->SetSize(((Vector2f)spriteOffset.renderPixelSize + v) * spriteOffset.scale, PseudoRenderBox);
				Objects[Bell][Objects[Bell].size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case  Hook:
			{
				SpriteOffsetData spriteOffset(Vector2i(34, 29), Vector2i(125, 212), Vector2f(70, 70), Vector2f(0, 70), Vector2f(0, -40), float(0.80));
				Objects[Hook].push_back(Instantiate<Area>("Hook"));
				Objects[Hook][Objects[Hook].size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[Hook][Objects[Hook].size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Hook)]);
				Objects[Hook][Objects[Hook].size() - 1].lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
				Objects[Hook][Objects[Hook].size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case  Portal:
			{
				SpriteOffsetData spriteOffset(Vector2i(1, 21), Vector2i(188, 177), Vector2f(150, 80), Vector2f(0, 38), Vector2f(0, -20), float(0.85));
				Objects[Portal].push_back(Instantiate<PortalClass>("Portal"));
				Objects[Portal][Objects[Portal].size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[Portal][Objects[Portal].size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Portal)]);
				Objects[Portal][Objects[Portal].size() - 1].lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
				Objects[Portal][Objects[Portal].size() - 1].lock()->GetTransform()->SetSize(Objects[Portal][Objects[Portal].size() - 1].lock()->GetTransform()->pseudoRenderBox.getSize() - Vector2f(15, 15), PseudoRenderBox);
				Objects[Portal][Objects[Portal].size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				if (Portals[roomData.objects[i][j] % 10].expired())
					Portals[roomData.objects[i][j] % 10] = dynamic_pointer_cast<PortalClass>(Objects[Portal][Objects[Portal].size() - 1].lock());
				else {
					weak_ptr<PortalClass> wp = dynamic_pointer_cast<PortalClass>(Objects[Portal][Objects[Portal].size() - 1].lock());
					Portals[roomData.objects[i][j] % 10].lock()->Linking(wp);
					wp.lock()->Linking(Portals[roomData.objects[i][j] % 10]);
				}
				break;
			}
			case  Strawberry:
			{
				SpriteOffsetData spriteOffset(Vector2i(22, 9), Vector2i(154, 205), Vector2f(120, 60), Vector2f(0, 70), Vector2f(0, -32), float(0.75));
				Objects[Strawberry].push_back(Instantiate<StrawberryClass>("Strawberry"));
				Objects[Strawberry][Objects[Strawberry].size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[Strawberry][Objects[Strawberry].size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Strawberry)]);
				Objects[Strawberry][Objects[Strawberry].size() - 1].lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
				Objects[Strawberry][Objects[Strawberry].size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case  MovingPlatform:
			{
				SpriteOffsetData spriteOffset(Vector2i(0, 0), Vector2i(190, 140), Vector2f(190, 140), Vector2f(0, 0), Vector2f(0, 0), float(1));
				Objects[MovingPlatform].push_back(Instantiate<Area>("Block"));
				Objects[MovingPlatform][Objects[MovingPlatform].size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[MovingPlatform][Objects[MovingPlatform].size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::MovingPlatform)]);
				Objects[MovingPlatform][Objects[MovingPlatform].size() - 1].lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
				Objects[MovingPlatform][Objects[MovingPlatform].size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case  Switch:
			{
				SpriteOffsetData spriteOffset(Vector2i(10, 11), Vector2i(172, 147), Vector2f(155, 40), Vector2f(-8, 60), Vector2f(5, -40), float(0.85));
				Objects[Switch].push_back(Instantiate<Area>("Block"));
				Objects[Switch][Objects[Switch].size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[Switch][Objects[Switch].size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::Switch)]);
				Objects[Switch][Objects[Switch].size() - 1].lock()->GetTransform()->SetAllSpriteOffset(spriteOffset);
				Objects[Switch][Objects[Switch].size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case  ObjectType::PlacingSwitch:
			{
				break;
			}
			case  ObjectType::NormalBlock:
			{
				SpriteOffsetData spriteOffset(Vector2i(0, 0), Vector2i(150, 250), Vector2f(150, 140), Vector2f(0, 55), Vector2f(0, -55), float(1));
				Objects[NormalBlock].push_back(Instantiate<NormalBlockClass>("NormalBlock"));
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::NormalBlock)]);
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->SetAllSpriteOffset(spriteOffset,Vector2f(190./140,1));
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->SetSize(Vector2f(190, 140), PseudoRenderBox);
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->MoveOffset(Vector2f(0, 55), PseudoRenderBox);
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case  ObjectType::DeleteBlock:
			{
				SpriteOffsetData spriteOffset(Vector2i(0, 0), Vector2i(150, 250), Vector2f(150, 140), Vector2f(0, 55), Vector2f(0, -55), float(1));
				Objects[DeleteBlock].push_back(Instantiate<DeleteBlockClass>("DeleteBlock"));
				Objects[DeleteBlock][Objects[DeleteBlock].size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[DeleteBlock][Objects[DeleteBlock].size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::DeleteBlock)]);
				Objects[DeleteBlock][Objects[DeleteBlock].size() - 1].lock()->GetTransform()->SetAllSpriteOffset(spriteOffset, Vector2f(190. / 140, 1));
				Objects[DeleteBlock][Objects[DeleteBlock].size() - 1].lock()->GetTransform()->SetSize(Vector2f(190, 140), PseudoRenderBox);
				Objects[DeleteBlock][Objects[DeleteBlock].size() - 1].lock()->GetTransform()->MoveOffset(Vector2f(0, 55), PseudoRenderBox);
				Objects[DeleteBlock][Objects[DeleteBlock].size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case  ObjectType::SignalBlock:
			{
				SpriteOffsetData spriteOffset(Vector2i(0, 0), Vector2i(150, 250), Vector2f(150, 140), Vector2f(0, 55), Vector2f(0, -55), float(1));
				Objects[NormalBlock].push_back(Instantiate<NormalBlockClass>("SignalBlock"));
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::SignalBlock)]);
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->SetAllSpriteOffset(spriteOffset, Vector2f(190. / 140, 1));
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->SetSize(Vector2f(190, 140), PseudoRenderBox);
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->MoveOffset(Vector2f(0, 55), PseudoRenderBox);
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			case  ObjectType::MoveableBlock:
			{
				SpriteOffsetData spriteOffset(Vector2i(0, 0), Vector2i(150, 250), Vector2f(150, 140), Vector2f(0, 55), Vector2f(0, -55), float(1));
				Objects[NormalBlock].push_back(Instantiate<NormalBlockClass>("NormalBlock"));
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::PlayerAndObject);
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->renderBox.setTexture(&WControl::objectsPrefab()[ObjectTypeToString(ObjectType::MoveableBlock)]);
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->SetAllSpriteOffset(spriteOffset, Vector2f(190. / 140, 1));
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->SetSize(Vector2f(190, 140), PseudoRenderBox);
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->MoveOffset(Vector2f(0, 55), PseudoRenderBox);
				Objects[NormalBlock][Objects[NormalBlock].size() - 1].lock()->GetTransform()->pseudoRenderBox.setFillColor(Color::Yellow);
				break;
			}
			}
		}
	}
}
void Room::ResetRoom() {
	for (auto it = Objects.begin(); it != Objects.end(); it++) {
		for (size_t i = 0; i < Objects.size(); i++)
		{
			type_index typeindex = it->second[i].lock()->GetTransform()->typeIndex;
			Destroy(it->second[i], typeindex);
		}
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
				areas[i][j].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::Floor, Color::Magenta);
			else
				areas[i][j].lock()->GetTransform()->SetAll(dynamic_pointer_cast<Tilemap>(transform->wp.lock()), Vector2i(j + 1, i + 1)
					, RenderPriorityType::Floor, Color::Black);
		}
	}
}

void Room::Update() {
	if (WorldControl::isGamePlaying() && WControl::GetCurrentRoomPosition() == roomPosition)
	{
		CheckCollisionInRoom();
	}
}

void Room::CheckCollisionInRoom() {
	WControl::player().lock()->lastFrameHitBox = WControl::player().lock()->transform->hitBox;
	CheckCollisionBetweenPlayerAndRoomEdge();
	CheckCollisionBetweenPlayerAndObject();
	CheckCollisionBetweenPlayerAndWall();
	CheckCollisionOfKnife();
	if (WControl::player().lock()->isHooking)
		CheckCollisionBetweenPlayerAndHookingCancler();
	CheckUICollision();
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
		startTime = clock();
		Vector2f distance = WControl::player().lock()->transform->position - MiddlePositionOfRoom();
		int x = roomPosition.x, y = roomPosition.y;
		if (abs(distance.x) > abs(distance.y)) {
			if (distance.x >= 0) {
				if (x + 1 < 5) {
					WControl::SetCurrentRoomPositon(Vector2i(++x, y));
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(1, RSIZEY / 2 + 0.5));
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
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(RSIZEX, RSIZEY / 2 + 0.5));
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
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(RSIZEX / 2 + 0.5, 1));
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
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(RSIZEX / 2 + 0.5, RSIZEY));
					printf("%d %d Up\n", roomPosition.x, roomPosition.y);
				}
				else {
					WControl::player().lock()->transform->position =
						GetTransform()->GetTile().lock()->GetRealPositionAt(WControl::GetCurrentRoomPosition(), Vector2f(RSIZEX / 2 + 0.5, 1));
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
		WControl::player().lock()->lastFrameHitBox = WControl::player().lock()->transform->hitBox;
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
	else {
		//printf("In");
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
	for (int i = 0; i < KnifeInteractableObjectTypes().size(); i++) {
		ObjectType obj = KnifeInteractableObjectTypes()[i];
		vector<weak_ptr<Area> > v;
		for (size_t j = 0; j < Objects[obj].size(); j++)
		{
			if (!Objects[obj][j].expired()) {
				queue<weak_ptr<Knife>> knifes = WControl::player().lock()->knifes;
				queue<weak_ptr<Knife>> newKnifes;
				while (!knifes.empty())
				{
					weak_ptr<Knife> knife = knifes.front();
					knifes.pop();
					if (!knife.expired()) {
						newKnifes.push(knife);
						if (!knife.lock()->GetIsStop()&&Collision::isCollision(knife.lock()->transform->pseudoRenderBox, Objects[obj][j].lock()->GetTransform()->hitBox)) {
							weak_ptr<KnifeInteractable> wp = dynamic_pointer_cast<KnifeInteractable>(Objects[obj][j].lock());
							if (!wp.expired()) {
								wp.lock()->interacting(knife);
							}
						}
					}
				}
				WControl::player().lock()->knifes = newKnifes;

				v.push_back(Objects[obj][j]);
			}
		}
		Objects[obj] = v;

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
		WControl::getMainDungeon().Rooms[y][x + 1].lock()->SetAllObjectsInRoom(WControl::usedRoomPrefabs()[GetRoomType(Align::HoriZontal, Vector2i(x + 1, y))][0]);
	}
	if (x - 1 >= 0 && !WControl::getMainDungeon().havePast[y][x - 1] && WControl::getMainDungeon().bVerticleEdge[y][x]) {
		WControl::getMainDungeon().Rooms[y][x - 1].lock()->SetAllObjectsInRoom(WControl::usedRoomPrefabs()[GetRoomType(Align::HoriZontal, Vector2i(x - 1, y))][0]);
	}
	if (y + 1 < 5 && !WControl::getMainDungeon().havePast[y + 1][x] && WControl::getMainDungeon().bHorizonEdge[y + 1][x]) {
		WControl::getMainDungeon().Rooms[y + 1][x].lock()->SetAllObjectsInRoom(WControl::usedRoomPrefabs()[GetRoomType(Align::Verticle, Vector2i(x, y + 1))][0]);
	}
	if (y - 1 >= 0 && !WControl::getMainDungeon().havePast[y - 1][x] && WControl::getMainDungeon().bHorizonEdge[y][x]) {
		WControl::getMainDungeon().Rooms[y - 1][x].lock()->SetAllObjectsInRoom(WControl::usedRoomPrefabs()[GetRoomType(Align::Verticle, Vector2i(x, y - 1))][0]);
	}
}

void Room::CheckUICollision()
{
	Vector2f cursurPos = WControl::view().getCenter() - Multiple(WControl::view().getSize(), Vector2f(0.5, 0.5));
	cursurPos += Multiple(Vector2f(1/WControl::WorldScale(), 1/WControl::WorldScale()), (Vector2f)Mouse::getPosition(WControl::window()));
	if (!WControl::clickableSpriteAtCursor().expired()) {
		if (!Collision::isCollision(WControl::clickableSpriteAtCursor().lock()->transform->hitBox, cursurPos)&&!Mouse::isButtonPressed(Mouse::Button::Left)){
			WControl::clickableSpriteAtCursor().reset();
		}
		else
			return;
	}
	if (!WControl::UIStack().empty()) {
		for(auto wp : WControl::AllUI()[WControl::UIStack().top()].clickableSprites) {
			if (Collision::isCollision(wp.lock()->transform->hitBox, cursurPos)) {
				WControl::clickableSpriteAtCursor() = wp;
				wp.lock()->transform->renderBox.setFillColor(Color::Yellow);
			}
			else {
				wp.lock()->transform->renderBox.setFillColor(Color::White);
			}
		}
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
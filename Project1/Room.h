#pragma once
#include "Tile.h"
#include "Walkable.h"
#include "PortalClass.h"
#include <array>
#include <string>
#include "Input.h"
#include "Output.h"
#define RSIZEX 8
#define RSIZEY 6
enum  Align
{
	Verticle,
	HoriZontal
};
enum ObjectType {
	Null,
	ChargeSoul,
	Bell,
	Hook,
	Portal,
	Strawberry,
	MovingPlatform,
	Switch,
	NormalBlock,
	DeleteBlock,
	SignalBlock,
	MoveableBlock,
	PlacingSwitch,
	Laser,
	Key
	
};
enum RoomType {
	Type00,
	Type01,
	Type02,
	Type10,
	Type11_Horizon,
	Type11_Verticle,
	Type12_Horizon,
	Type12_Verticle,
	Type20,
	Type21_Horizon,
	Type21_Verticle,
	Type22_Horizon,
	Type22_Verticle
};
struct SwitchGroup {
	weak_ptr<Input> input;
	vector<weak_ptr<Output> > outputs;
	void clear(); 
};
struct RoomData
{
	RoomData(std::string s) :name(s), floor(RSIZEY, vector<bool>(RSIZEX, false)), objects(RSIZEY, vector<int>(RSIZEX, 0)), track(RSIZEY, vector<int>(RSIZEX, 0)) {}
	RoomData() :floor(RSIZEY, vector<bool>(RSIZEX, false)), objects(RSIZEY, vector<int>(RSIZEX, 0)), track(RSIZEY, vector<int>(RSIZEX, 0)) {}
	std::string name = "null";
	RoomType roomType = RoomType::Type00;
	std::vector<vector<bool> > floor;
	std::vector<vector<int> > objects;
	std::vector<vector<int> > track;
	int BerryAmount = 0;
};
class Room:public Tilemap
{
	vector<weak_ptr<PortalClass>> Portals = vector<weak_ptr<PortalClass>>(10, weak_ptr<PortalClass>());
	RoomData originalRoomData;
	RoomData roomData;
	Vector2i roomPosition;
	void SetAllObjectsInRoom();
	void SetFloor();
public:
	SwitchGroup  switchGroups[10];
	map<ObjectType, vector<weak_ptr<Area> > > Objects;
	vector<vector<weak_ptr<GameSprite>>> Space= vector<vector<weak_ptr<GameSprite>>>(RSIZEY,vector<weak_ptr<GameSprite>>(RSIZEX,weak_ptr<GameSprite>()));
	Vector2f startRoomPosition;
	weak_ptr<Area> areas[RSIZEY][RSIZEX];
	vector<weak_ptr<Area> > Walls[6];
	vector<weak_ptr<Area> > cliffs;
	std::array<std::array<bool, RSIZEX+2>, RSIZEY+2> cannotPush;

	static const vector<ObjectType>& WalkableObjectTypes();
	static const vector<ObjectType>& UnwalkableObjectTypes();
	static const vector<ObjectType>& MeleeAttackableObjectTypes();
	static const vector<ObjectType>& HookAbleableObjectTypes();
	static const vector<ObjectType>& HookingCanclerObjectTypes();
	static const vector<ObjectType>& KnifeInteractableObjectTypes();

	Room();
	Room(std::string s);
	
	void SetRoom(const Vector2i& roomPosition);
	void SetRoomSeed(const RoomData& roomData,const bool& isFlipX,const bool& isFlipY);

	void ResetRoom();
	void RestartRoom();
	void LoadNearbyRoom();
	void Update() override;
	void UnLoadNearbyRoom();

	void DestroyAllEdge();
	void DestroyAllObjects();
	
	const Vector2f& MiddlePositionOfRoom();
	const Vector2f& TopLeftPositionOfRoom();
	
	static RoomType GetRoomType(const Direction& direction, Vector2i roomPosition, bool* FlipX, bool* FlipY);
	static void SetObjectTypeString();
	static std::string ObjectTypeToString(const ObjectType& objectType);
	
	void CheckCollisionBetweenAttackHitBoxAndObject();
	void CheckCollisionRingHitBoxAndMeleeAttackableObject(weak_ptr<GameSprite> bell);
	void CheckNearestObjectHooking();
	void CheckCollisionWithMoveableBlock();

	void InstantChargeSoul(const Vector2i& pos);
	void InstantBell(const Vector2i& pos);
	void InstantHook(const Vector2i& pos);
	void InstantPortal(const Vector2i& pos);
	void InstantKey(const Vector2i& pos);
	void InstantStrawberry(const Vector2i& pos);
	void InstantMovingPlatform(const Vector2i& pos);
	void InstantSwitch(const Vector2i& pos);
	void InstantNormalBlock(const Vector2i& pos);
	void InstantDeleteBlock(const Vector2i& pos);
	void InstantSignalBlock(const Vector2i& pos);
	void InstantMoveableBlock(const Vector2i& pos);
	void InstantPlacingSwitch(const Vector2i& pos);
	void InstantLaser(const Vector2i& pos);
private:
	static void getSumOfAlignEdge(int& xSum, int& ySum, const int& x, const int& y);
	static RoomType GetRoomType(const Direction& direction, const int& xSum, const int& ySum);
	
	void CheckCollisionInRoom();
	
	void CheckCollisionBetweenPlayerAndWall();
	void CheckCollisionBetweenPlayerAndObject();
	void CheckCollisionBetweenPlayerAndRoomEdge();
	void CheckCollisionBetweenPlayerAndCliff();
	
	void CheckCollisionBetweenPlayerAndHookingCancler();
	void CheckCollisionOfKnife();
};

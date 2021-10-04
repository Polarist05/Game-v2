#pragma once
#include "Tile.h"
#include <string>
#define RSIZEX 8
#define RSIZEY 6
enum  Align
{
	Verticle,
	HoriZontal
};
enum ObjectType {
	Switch,
	PlacingSwitch,
	Gate,
	Laser,
	Portal,
	ChargeSoul,
	Bell,
	Hook,
	Strawberry,
	Stone,
	MovingPlatform,
	Null
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
struct RoomData
{
	RoomData() :floor(RSIZEY, vector<bool>(RSIZEX, false)), objects(RSIZEY, vector<int>(RSIZEX, 0)), track(RSIZEY, vector<int>(RSIZEX, 0)) {}
	std::string name = "null";
	RoomType roomType = RoomType::Type00;
	std::vector<vector<bool> > floor;
	std::vector<vector<int> > objects;
	std::vector<vector<int> > track;
};
class Room:public Tilemap
{
	RoomData rooomData;
	vector<weak_ptr<Area> > Objects;
	Vector2i roomPosition;
public:
	Room();
	Room(std::string s);
	void SetRoom(const Vector2i& roomPosition);
	weak_ptr<Area> areas[RSIZEY][RSIZEX];
	void SetRoom1(RoomData roomData);
	void ResetRoom();
	void SetFloor();
	void SetObject();
	void LoadNearbyRoom();
	void Update() override;
	void UnLoadNearbyRoom();
	Vector2f MiddlePositionOfRoom();
	static RoomType GetRoomType(const Align& align, Vector2i roomPosition);
	static void SetObjectTypeString();
	static std::string ObjectTypeToString(const ObjectType& objectType);
private:
	static void getSumOfAlignEdge(int& xSum, int& ySum, const int& x, const int& y);
	static RoomType GetRoomType(const Align& align, const int& xSum, const int& ySum);
	void CheckCollisionInRoom();
	void CheckCollisionBetweenPlayerAndWall();
};

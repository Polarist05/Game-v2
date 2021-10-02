#pragma once
#include "Tile.h"
#include <string>
#define RSIZEX 8
#define RSIZEY 6
enum ObjectType {
	Switch,
	PlacingSwitch,
	Gate,
	Laser,
	Portal,
	SoulCharge,
	Bell,
	Hook,
	Berry,
	Stone,
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
	RoomData rooomdata;
public:
	Room();
	Room(std::string s);
	weak_ptr<Area> areas[RSIZEY][RSIZEX];
	void SetRoom();
	void SetFloor();
	void SetObject();
	void LoadallObject();
	void LoadNearbyRoom();
	void Update() override;
private:
	void CheckCollisionInRoom();
	void CheckCollisionBetweenPlayerAndWall();
};

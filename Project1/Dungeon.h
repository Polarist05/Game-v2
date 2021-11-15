#pragma once
#include <queue>
#include "SFML.h"
#include "Room.h"
#include <vector>
#include <array>
using namespace std;
class Dungeon
{	
	Vector2i startRoom;
	std::array<Vector2i,3> roomKey;
public:
	Vector2i getStartRoom();
	std::array<Vector2i, 3> GetKeyRoom();
	bool bHorizonEdge[6][5] = {}, bVerticleEdge[5][6] = {};
	bool havePast[5][5] = {};
	vector<vector< weak_ptr<Room> > > Rooms;
	vector<weak_ptr<Area> > EdgeFloors;
	void PrintDungeon();
	void GenerateDungeon();
	void GenerateToolkitMode();
	void ResetDungeon();
	Dungeon();
private:
	void ChooseKeyRoom();
	void InstantEdge();
	void GenerateMaze();
	void InstantRoom();
	std::string EnumDirectionName(int a);
	void RandomEdge(int(*horizonEdge)[5], int(*verticleEdge)[6]);
	void pushDepthQueue(Vector2i v, bool(*arr)[5], std::priority_queue<pair< pair<int, bool*>, int> >& pq, int weight
					,int(*horizonEdge)[5], int(*verticleEdge)[6]);
	void MakeEdges(int(*horizonEdge)[5], int(*verticleEdge)[6]);
	void RunDepth(int(*arr)[5], Vector2i startPosition);
	void BreakWall();
	Vector2i FindMaxAndReturnPos(int(*arr)[5]);
	RoomType CollectRoomType(Vector2i room,Direction direction);
};
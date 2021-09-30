#pragma once
#include <queue>
#include "SFML.h"
#include "Room.h"
#include <vector>
using namespace std;
enum Direction
{
	Up,
	Down,
	Right,
	Left
};
struct RoomData
{
	RoomData() :floor(RSIZEY,vector<bool>(RSIZEX,false)),objects(RSIZEY, vector<int>(RSIZEX, 0)),track(RSIZEY, vector<int>(RSIZEX, 0)){}
	std::string name = "null";
	RoomType roomType = RoomType::Type00;
	std::vector<vector<bool> > floor;
	std::vector<vector<int> > objects;
	std::vector<vector<int> > track;
};
class Dungeon
{
	bool bHorizonEdge[6][5] = {}, bVerticleEdge[5][6] = {};
	Vector2i startPosition;
public:
	vector<vector< weak_ptr<Room> > > Rooms;
	void PrintDungeon();
	Dungeon();
private:
	std::string EnumDirectionName(int a);
	void RandomEdge(int(*horizonEdge)[5], int(*verticleEdge)[6]);
	void pushQueue(Vector2i v, bool(*arr)[5], std::priority_queue<pair< pair<int, bool*>, int> >& pq, int weight
					,int(*horizonEdge)[5], int(*verticleEdge)[6]);
	void MakeEdges(int(*horizonEdge)[5], int(*verticleEdge)[6]);
	void RunDepth(int(*arr)[5], Vector2i startPosition);
	void GetBreakWallPos();
	Vector2i FindMax(int(*arr)[5]);
	RoomType CollectRoomType(Vector2i room,Direction direction);
};
void LoadAllRoomPrefab();
void SaveAllRoomPrefab();
void SetUsedRoomPrefab();
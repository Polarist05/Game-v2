#pragma once
#include <queue>
#include "SFML.h"
using namespace std;
enum Direction
{
	Up,
	Down,
	Right,
	Left
};
class Dungeon
{
	bool bHorizonEdge[6][5] = {}, bVerticleEdge[5][6] = {};
	Vector2i startPosition;
public:
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
};


#include "Dungeon.h"
#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "WorldControl.h"
#include <fstream>
#include <filesystem>
#include <random>

Vector2i Dungeon::getStartRoom() { return startRoom; }

std::array<Vector2i, 3> Dungeon::GetKeyRoom()
{
	return roomKey;
}

void Dungeon::GenerateDungeon()
{
	GenerateMaze();
	InstantEdge();
	WControl::SetCurrentRoomPositon(Vector2i(startRoom.x, startRoom.y));
	WControl::getMainDungeon().havePast[startRoom.y][startRoom.x] = true;
	WControl::player().lock()->ResetSoul();
	Rooms[startRoom.y][startRoom.x].lock()->SetRoomSeed(WControl::allRoomPrefabs()["startRoom"].second[0],false,false);
	Rooms[startRoom.y][startRoom.x].lock()->LoadNearbyRoom();
	WControl::player().lock()->transform->SetPosition(Rooms[startRoom.y][startRoom.x].lock()->GetTransform()->GetTile().lock()->GetRealPositionAt(Vector2i(startRoom.x, startRoom.y), Vector2f(3, 2.5)));
	
}
void Dungeon::GenerateToolkitMode()
{
	InstantEdge();
	WControl::SetCurrentRoomPositon(Vector2i(0, 0));
	WControl::player().lock()->transform->position = WControl::GetCurrentRoom().lock()->transform->position + 
		Multiple(WControl::MainTile().lock()->GetAreaSize(),Vector2f(2,2));
	WControl::GetCurrentRoom().lock()->SetRoomSeed(RoomData(), false, false);
}
void Dungeon::ResetDungeon()
{
	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			bHorizonEdge[i][j] = false;
			bVerticleEdge[j][i] = false;
		}
	}
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			havePast[i][j] = false;
		}
	}

	for (auto edgeFloor : EdgeFloors) {
		weak_ptr<GameSprite> wp = edgeFloor.lock()->transform->wp;
		type_index typeI = wp.lock()->transform->typeIndex;
		Destroy(wp, typeI);
	}
	EdgeFloors.clear();

	for (auto i : Rooms) {
		for (auto room : i) {
			room.lock()->DestroyAllEdge();
			room.lock()->DestroyAllObjects();
		}
	}
}

Dungeon::Dungeon() {
	WControl::setMainDungeon(this);
	InstantRoom();
	WControl::SetCurrentRoomPositon(Vector2i(0, 0));
}
void Dungeon::ChooseKeyRoom()
{
	int x,y;
	for (int i = 0;i<3;i++) {
		int j ;
		do {
			x = rand() % 5;
			y = rand() % 5;
			for (j=0;j<i;j++) {
				if (x == roomKey[j].x && y == roomKey[j].y)
					break;
			}
		} while ((x == startRoom.x && y == startRoom.y)||j!=i);
		roomKey[i].x = x; roomKey[i].y = y;
	}
}

void Dungeon::InstantEdge() {
	Color color(32, 32, 32, 255);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			int middleX = RSIZEX / 2, middleY = RSIZEY / 2;
			if (bVerticleEdge[i][j]) {
				EdgeFloors.push_back(Instantiate<Area>("Edge"));
				EdgeFloors[EdgeFloors.size() - 1].lock()->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
					, Vector2i(0, middleY), RenderPriorityType::Floor, Color::Cyan);
				EdgeFloors.push_back(Instantiate<Area>("Edge"));
				EdgeFloors[EdgeFloors.size() - 1].lock()->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
					, Vector2i(0, middleY + 1), RenderPriorityType::Floor, Color::Cyan);
				{
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left].push_back(Instantiate<Area>("Wall"));
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left].size() - 1].lock()
						->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
							, Vector2i(0, 0), RenderPriorityType::Floor, color);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left].size() - 1].lock()
						->GetTransform()->SetAnchorType(AnchorType::TopCentor, RenderBox, FIX_ALL_RECT_POSITION);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left].size() - 1].lock()
						->GetTransform()->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(1, RSIZEY /2)), RenderBox);
				}
				{
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left].push_back(Instantiate<Area>("Wall"));
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left].size() - 1].lock()
						->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
							, Vector2i(0, RSIZEY+1), RenderPriorityType::Floor, color);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left].size() - 1].lock()
						->GetTransform()->SetAnchorType(AnchorType::DownCentor, RenderBox, FIX_ALL_RECT_POSITION);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left].size() - 1].lock()
						->GetTransform()->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(1, RSIZEY / 2)), RenderBox);
				}
			}
			else {
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left].push_back(Instantiate<Area>("Wall"));
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left].size() - 1].lock()
					->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
						, Vector2i(0,0), RenderPriorityType::Floor, color);
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left].size() - 1].lock()
					->GetTransform()->SetAnchorType(AnchorType::TopCentor, RenderBox, FIX_ALL_RECT_POSITION);
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Left].size() - 1].lock()
					->GetTransform()->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(),Vector2f(1,RSIZEY+2)),RenderBox);
			}
			if (bVerticleEdge[i][j + 1]) {
				EdgeFloors.push_back(Instantiate<Area>("Edge"));
				EdgeFloors[EdgeFloors.size() - 1].lock()->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
					, Vector2i(RSIZEX + 1, middleY), RenderPriorityType::Floor, Color::Cyan);
				EdgeFloors.push_back(Instantiate<Area>("Edge"));
				EdgeFloors[EdgeFloors.size() - 1].lock()->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
					, Vector2i(RSIZEX + 1, middleY + 1), RenderPriorityType::Floor, Color::Cyan);
				{
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right].push_back(Instantiate<Area>("Wall"));
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right].size() - 1].lock()
						->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
							, Vector2i(RSIZEX + 1, 0), RenderPriorityType::Floor, color);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right].size() - 1].lock()
						->GetTransform()->SetAnchorType(AnchorType::TopCentor, RenderBox, FIX_ALL_RECT_POSITION);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right].size() - 1].lock()
						->GetTransform()->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(1, RSIZEY / 2)), RenderBox);
				}
				{
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right].push_back(Instantiate<Area>("Wall"));
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right].size() - 1].lock()
						->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
							, Vector2i(RSIZEX + 1, RSIZEY + 1), RenderPriorityType::Floor, color);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right].size() - 1].lock()
						->GetTransform()->SetAnchorType(AnchorType::DownCentor, RenderBox, FIX_ALL_RECT_POSITION);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right].size() - 1].lock()
						->GetTransform()->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(1, RSIZEY / 2)), RenderBox);
				}
			}
			else {
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right].push_back(Instantiate<Area>("Wall"));
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right].size() - 1].lock()
					->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
						, Vector2i(RSIZEX+1, 0), RenderPriorityType::Floor, color);
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right].size() - 1].lock()
					->GetTransform()->SetAnchorType(AnchorType::TopCentor, RenderBox, FIX_ALL_RECT_POSITION);
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Right].size() - 1].lock()
					->GetTransform()->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(1, RSIZEY+2)), RenderBox);
			}
			if (bHorizonEdge[i][j]) {
				EdgeFloors.push_back(Instantiate<Area>("Edge"));
				EdgeFloors[EdgeFloors.size() - 1].lock()->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
					, Vector2i(middleX, 0), RenderPriorityType::Floor, Color::Cyan);
				EdgeFloors.push_back(Instantiate<Area>("Edge"));
				EdgeFloors[EdgeFloors.size() - 1].lock()->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
					, Vector2i(middleX + 1, 0), RenderPriorityType::Floor, Color::Cyan);
				{
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up].push_back(Instantiate<Area>("Wall"));
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up].size() - 1].lock()
						->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
							, Vector2i(0, 0), RenderPriorityType::Floor, color);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up].size() - 1].lock()
						->GetTransform()->SetAnchorType(AnchorType::TopLeft, RenderBox, FIX_ALL_RECT_POSITION);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up].size() - 1].lock()
						->GetTransform()->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(RSIZEX/2, 1)), RenderBox);
				}
				{
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up].push_back(Instantiate<Area>("Wall"));
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up].size() - 1].lock()
						->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
							, Vector2i(RSIZEX + 1, 0), RenderPriorityType::Floor, color);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up].size() - 1].lock()
						->GetTransform()->SetAnchorType(AnchorType::TopRight, RenderBox, FIX_ALL_RECT_POSITION);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up].size() - 1].lock()
						->GetTransform()->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(RSIZEX/2,1)), RenderBox);
				}
			}
			else {
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up].push_back(Instantiate<Area>("Wall"));
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up].size() - 1].lock()
					->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
						, Vector2i(0, 0), RenderPriorityType::Floor, color);
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up].size() - 1].lock()
					->GetTransform()->SetAnchorType(AnchorType::MiddleLeft, RenderBox, FIX_ALL_RECT_POSITION);
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Up].size() - 1].lock()
					->GetTransform()->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(RSIZEX+2,1)), RenderBox);
			}
			if (bHorizonEdge[i + 1][j]) {
				EdgeFloors.push_back(Instantiate<Area>());
				EdgeFloors[EdgeFloors.size() - 1].lock()->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
					, Vector2i(middleX, RSIZEY + 1), RenderPriorityType::Floor, Color::Cyan);
				EdgeFloors.push_back(Instantiate<Area>());
				EdgeFloors[EdgeFloors.size() - 1].lock()->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
					, Vector2i(middleX + 1, RSIZEY + 1), RenderPriorityType::Floor, Color::Cyan);
				{
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down].push_back(Instantiate<Area>("Wall"));
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down].size() - 1].lock()
						->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
							, Vector2i(0, RSIZEY+1), RenderPriorityType::Floor, color);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down].size() - 1].lock()
						->GetTransform()->SetAnchorType(AnchorType::TopLeft, RenderBox, FIX_ALL_RECT_POSITION);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down].size() - 1].lock()
						->GetTransform()->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(RSIZEX / 2, 1)), RenderBox);
				}
				{
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down].push_back(Instantiate<Area>("Wall"));
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down].size() - 1].lock()
						->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
							, Vector2i(RSIZEX + 1, RSIZEY+1), RenderPriorityType::Floor, color);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down].size() - 1].lock()
						->GetTransform()->SetAnchorType(AnchorType::TopRight, RenderBox, FIX_ALL_RECT_POSITION);
					WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down].size() - 1].lock()
						->GetTransform()->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(RSIZEX / 2, 1)), RenderBox);
				}
			}
			else {
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down].push_back(Instantiate<Area>("Wall"));
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down].size() - 1].lock()
					->GetTransform()->SetAll(WControl::getMainDungeon().Rooms[i][j].lock()
						, Vector2i(0, RSIZEY+1), RenderPriorityType::Floor, color);
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down].size() - 1].lock()
					->GetTransform()->SetAnchorType(AnchorType::MiddleLeft, RenderBox, FIX_ALL_RECT_POSITION);
				WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down][WControl::getMainDungeon().Rooms[i][j].lock()->Walls[Direction::Down].size() - 1].lock()
					->GetTransform()->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(RSIZEX + 2, 1)), RenderBox);
			}
		}
	}
}
void Dungeon::GenerateMaze() {
	int horizonEdgeWeight[6][5] = {}, verticleEdgeWeight[5][6] = {};
	RandomEdge(horizonEdgeWeight, verticleEdgeWeight);
	MakeEdges(horizonEdgeWeight, verticleEdgeWeight);
	startRoom = Vector2i(rand() % 5, rand() % 5);
	printf("Start position is %d %d\n", startRoom.y, startRoom.x);
	for (int i = 0; i < 3; i++)
		BreakWall(); 
	ChooseKeyRoom();
	PrintDungeon();
}
void Dungeon::InstantRoom() {
	for (int i = 0; i < 5; i++) {
		Rooms.push_back(vector<weak_ptr<Room> >());
		for (int j = 0; j < 5; j++) {
			Rooms[i].push_back(Instantiate<Room>("Room" + to_string(i) + to_string(j)));
			Rooms[i][j].lock()->SetRoom(Vector2i(j, i));
			Rooms[i][j].lock()->GetTransform()->SetParent(WorldControl::MainTile(), Vector2i((RSIZEX + 2) * j, (RSIZEY + 2) * i));

			//extension
			Vector2f boxSize = Rooms[i][j].lock()->GetTransform()->GetTile().lock()->GetRealRoomSize() - Rooms[i][j].lock()->GetTransform()->GetAreaSize();
			Rooms[i][j].lock()->GetTransform()->renderBox.setFillColor(Color::White);
			Rooms[i][j].lock()->GetTransform()->SetSize(boxSize, BoxType::RenderBox);
			//
			Rooms[i][j].lock()->GetTransform()->SetPositionOffset(Multiple(boxSize,Vector2f(0.5,0.5)), BoxType::RenderBox);
		}
	}
}
RoomType Dungeon::CollectRoomType(Vector2i v, Direction direction) {
	int yAmount = (int)bHorizonEdge[v.y] + (int)bHorizonEdge[v.y + 1];
	int xAmount = (int)bVerticleEdge[v.x] + (int)bVerticleEdge[v.x + 1];
	switch (yAmount * 3 + xAmount)
	{
	case 0:return RoomType::Type00; break;
	case 1:return RoomType::Type01; break;
	case 2:return RoomType::Type02; break;
	case 3:return RoomType::Type10; break;
	case 4:
		if (direction == Direction::Left || direction == Direction::Right)
			return RoomType::Type11_Horizon;
		else
			return RoomType::Type11_Verticle;
		break;
	case 5:
		if (direction == Direction::Left || direction == Direction::Right)
			return RoomType::Type12_Horizon;
		else
			return RoomType::Type12_Verticle;
		break;
	case 6:return RoomType::Type20; break;
	case 7:
		if (direction == Direction::Left || direction == Direction::Right)
			return RoomType::Type21_Horizon;
		else
			return RoomType::Type21_Verticle;
		break;
	case 8: break;
		if (direction == Direction::Left || direction == Direction::Right)
			return RoomType::Type22_Horizon;
		else
			return RoomType::Type22_Verticle;
		break;
	}
}

// ForGenerateMaze
void Dungeon::RandomEdge(int(*horizonEdge)[5], int(*verticleEdge)[6]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			horizonEdge[i][j] = rand() % 80;
			verticleEdge[j][i] = rand() % 80;
		}
	}
}
void Dungeon::MakeEdges(int(*horizonEdge)[5], int(*verticleEdge)[6])
{
	std::priority_queue<pair< pair<int, bool* >, int> > pq;
	bool havePass[5][5] = {};
	pq.push({ { 0,&havePass[0][0]} ,4 });
	int count = 0;
	while (count < 25)
	{
		Vector2i pos((pq.top().first.second - &havePass[0][0]) % 5, ((pq.top().first.second - &havePass[0][0]) / 5) % 5);
		int weight = pq.top().first.first, direction = pq.top().second;
		pq.pop();

		if (!havePass[pos.y][pos.x])
		{
			count++;
			havePass[pos.y][pos.x] = true;
			pushDepthQueue(pos, havePass, pq, weight, horizonEdge, verticleEdge);
			switch (direction)
			{
			case Direction::Down:bHorizonEdge[pos.y][pos.x] = true; break;
			case Direction::Up:bHorizonEdge[pos.y + 1][pos.x] = true; break;
			case Direction::Right:bVerticleEdge[pos.y][pos.x] = true; break;
			case Direction::Left:bVerticleEdge[pos.y][pos.x + 1] = true; break;
			}
		}
	}
}
void Dungeon::RunDepth(int(*arr)[5], Vector2i startPosition)
{
	queue<Vector2i> q;
	q.push(startPosition);
	arr[startPosition.y][startPosition.x] = 1;
	while (!q.empty())
	{
		int y = q.front().y, x = q.front().x;
		if (bHorizonEdge[y][x] && !arr[y - 1][x]) {
			q.push(Vector2i(x, y - 1));
			arr[y - 1][x] = arr[y][x] + 1;
		}
		if (bHorizonEdge[y + 1][x] && !arr[y + 1][x]) {
			q.push(Vector2i(x, y + 1));
			arr[y + 1][x] = arr[y][x] + 1;
		}
		if (bVerticleEdge[y][x] && !arr[y][x - 1]) {
			q.push(Vector2i(x - 1, y));
			arr[y][x - 1] = arr[y][x] + 1;
		}
		if (bVerticleEdge[y][x + 1] && !arr[y][x + 1]) {
			q.push(Vector2i(x + 1, y));
			arr[y][x + 1] = arr[y][x] + 1;
		}
		q.pop();
	}
}
void Dungeon::pushDepthQueue(Vector2i v, bool(*arr)[5], std::priority_queue<pair< pair<int, bool*>, int> >& pq, int weight, int(*horizonEdge)[5], int(*verticleEdge)[6])
{
	if (v.x < 4)
	{
		if (!arr[v.y][v.x + 1])
		{
			pq.push({ { verticleEdge[v.y][v.x + 1],&arr[v.y][v.x + 1] }, Direction::Right });
		}
	}
	if (v.x > 0)
	{
		if (!arr[v.y][v.x - 1])
		{
			pq.push({ { verticleEdge[v.y][v.x],&arr[v.y][v.x - 1]},Direction::Left });
		}
	}
	if (v.y < 4)
	{
		if (!arr[v.y + 1][v.x])
		{
			pq.push({ { horizonEdge[v.y + 1][v.x],&arr[v.y + 1][v.x] },Direction::Down });
		}
	}
	if (v.y > 0)
	{
		if (!arr[v.y - 1][v.x])
		{
			pq.push({ { horizonEdge[v.y][v.x],&arr[v.y - 1][v.x] },Direction::Up });
		}
	}
}
void Dungeon::BreakWall() {
	Vector2i secondPosition;
	int firstDepth[5][5] = {}, secondDepth[5][5] = {}, horizontalMin = INT_MAX, VerticalMin = INT_MAX;
	RunDepth(firstDepth, startRoom);
	secondPosition = FindMaxAndReturnPos(firstDepth);
	RunDepth(secondDepth, secondPosition);
	Vector2i pos, pos1;
	//FindMinEdge
	for (int i = 1; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (!bHorizonEdge[i][j]) {
				int _mn = min(firstDepth[i - 1][j] + secondDepth[i][j], secondDepth[i - 1][j] + firstDepth[i][j]);
				if (horizontalMin > _mn) {
					horizontalMin = _mn;
					pos = Vector2i(i, j);
				}
			}
			if (!bVerticleEdge[j][i]) {
				int _mn = min(firstDepth[j][i - 1] + secondDepth[j][i], secondDepth[j][i - 1] + firstDepth[j][i]);
				if (VerticalMin > _mn) {
					VerticalMin = _mn;
					pos1 = Vector2i(j, i);
				}
			}
		}
	}
	if (horizontalMin <= VerticalMin) {
		bHorizonEdge[pos.x][pos.y] = true;
		printf("Delete Horizon: %d %d \n", pos.x, pos.y);
	}
	else {
		bVerticleEdge[pos1.x][pos1.y] = true;
		printf("Delete Verticle: %d %d \n", pos1.x, pos1.y);
	}
}
Vector2i Dungeon::FindMaxAndReturnPos(int(*arr)[5]) {
	int mx = INT_MIN;
	Vector2i ans;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (mx < arr[i][j])
			{
				mx = arr[i][j];
				ans = Vector2i(j, i);
			}
		}
	}
	return ans;
}

// Extention
void Dungeon::PrintDungeon() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("+");
			if (bHorizonEdge[i][j]) {
				printf(" ");
			}
			else {
				printf("-");
			}
		}
		printf("+");
		printf("\n");
		for (int j = 0; j < 6; j++) {
			if (bVerticleEdge[i][j]) {
				printf(" ");
			}
			else {
				printf("|");
			}
			if (j < 5) {
				bool b = false;
				for (size_t k = 0; k < 3; k++)
				{
					if (roomKey[k].x == j && roomKey[k].y == i)
						b = true;
				}
				if (startRoom.x == j && startRoom.y == i)
					printf("S");
				else if (b)
					printf("K");
				else
					printf(" ");
			}
		}
		printf("\n");
	}
	for (int j = 0; j < 5; j++) {
		printf("+");
		if (bHorizonEdge[5][j]) {
			printf(" ");
		}
		else {
			printf("-");
		}
	}
	printf("+\n");
	/*printf("key1 : %d %d\n", roomKey[0].x,roomKey[0].y);
	printf("key2 : %d %d\n", roomKey[1].x, roomKey[1].y);
	printf("key3 : %d %d\n", roomKey[2].x, roomKey[2].y);
	printf("StartRoom : %d %d\n", startRoom.x, startRoom.y);*/
}
std::string Dungeon::EnumDirectionName(int a) {
	const string direction[10] = { "Up","Down","Right","Left" ,"Null" };
	return direction[a];
}

// Local

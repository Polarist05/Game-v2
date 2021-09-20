#include "Dungeon.h"
#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <stdio.h>  
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
			if (j < 5)
				printf(" ");
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
}
Dungeon::Dungeon() {
	int horizonEdgeWeight[6][5] = {}, verticleEdgeWeight[5][6] = {};
	srand(time(NULL));
	RandomEdge(horizonEdgeWeight, verticleEdgeWeight);
	MakeEdges(horizonEdgeWeight, verticleEdgeWeight);
	startPosition = Vector2i(rand() % 5, rand() % 5);
	printf("Start position is %d %d\n", startPosition.y, startPosition.x);
	PrintDungeon();
	for (int i = 0; i < 3; i++)
		GetBreakWallPos();
	PrintDungeon();
}
std::string Dungeon::EnumDirectionName(int a) {
	const string direction[10] = { "Up","Down","Right","Left" ,"Null" };
	return direction[a];
}
void Dungeon::RandomEdge(int(*horizonEdge)[5], int(*verticleEdge)[6]) {
	int SumEachRoom[5][5];
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			horizonEdge[i][j] = rand() % 80;
			verticleEdge[j][i] = rand() % 80;
		}
	}
}
void Dungeon::pushQueue(Vector2i v, bool(*arr)[5], std::priority_queue<pair< pair<int, bool*>, int> >& pq, int weight, int(*horizonEdge)[5], int(*verticleEdge)[6])
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
			pushQueue(pos, havePass, pq, weight, horizonEdge, verticleEdge);
			switch (direction)
			{
			case Direction::Down:bHorizonEdge[pos.y][pos.x] = true; break;
			case Direction::Up:bHorizonEdge[pos.y + 1][pos.x] = true; break;
			case Direction::Right:bVerticleEdge[pos.y][pos.x] = true; break;
			case Direction::Left:bVerticleEdge[pos.y][pos.x + 1] = true; break;
			}
		}
		//cout << pos.y << " " << pos.x << " " << weight << " " << EnumDirectionName(direction) << endl;
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
void Dungeon::GetBreakWallPos() {
	Vector2i secondPosition;
	int firstDepth[5][5] = {}, secondDepth[5][5] = {}, horizontalMin = INT_MAX, VerticalMin = INT_MAX;
	RunDepth(firstDepth, startPosition);
	printf("\n");
	secondPosition = FindMax(firstDepth);
	RunDepth(secondDepth, secondPosition);
	Vector2i pos, pos1;
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
Vector2i Dungeon::FindMax(int(*arr)[5]) {
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
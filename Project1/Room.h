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
class Room:public Tilemap
{
	bool floor[RSIZEY][RSIZEX] = {};
	int objects[RSIZEY][RSIZEX] = {};
	bool track[RSIZEY][RSIZEX] = {};
public:
	Room(std::string s):Tilemap(s) {}
	weak_ptr<Area> areas[RSIZEX][RSIZEY];
	void f1() {
		for (int i = 0; i < RSIZEX; i++)
		{
			for (int j = 0; j < RSIZEY; j++)
			{
				areas[i][j] = Instantiate<Area>("123");
				areas[i][j].lock()->GetTransform()->SetParent(transform->wp, Vector2i(i - RSIZEX / 2, j - RSIZEY / 2));
				areas[i][j].lock()->GetTransform()->RenderPriority = RenderPriorityType::Floor;
				if ((i + j) % 2)
					areas[i][j].lock()->GetTransform()->renderBox.setFillColor(Color::Magenta);
				else
					areas[i][j].lock()->GetTransform()->renderBox.setFillColor(Color::Black);
				areas[i][j].lock()->GetTransform()->SetSize(GetTransform()->GetAreaSize(), BoxType::RenderBox);
			}
		}
	}
	void LoadallObject() {
		for (int i = 0; i < RSIZEY; i++) {
			for (int j = 0; j < RSIZEX; j++) {
				switch (objects[i][j]/10)
				{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				case 11:
					break;
				case 12:
					break;
				case 13:
					break;
				case 14:
					break;
				}
			}
		}
	}
	map<ObjectType,vector<GameSprite*>> allObjectinroom;
};

/*
* weak_ptr<Area> areas[RSIZEX][RSIZEY];
Room() {

}
void f1() {
	for (int i = 0; i < RSIZEX; i++)
	{
		for (int j = 0; j < RSIZEY; j++)
		{
			areas[i][j] = Instantiate<Area>(");
			areas[i][j].lock()->GetTransform()->SetParent(transform->wp, Vector2i(i-RSIZEX/2, j-RSIZEY/2));
				if ((i + j) % 2)
					areas[i][j].lock()->GetTransform()->renderBox.setFillColor(Color::Magenta);
				else
					areas[i][j].lock()->GetTransform()->renderBox.setFillColor(Color::Black);
			areas[i][j].lock()->GetTransform()->SetSize(GetTransform()->GetAreaSize(), BoxType::RenderBox);
		}
	}
}*/
#pragma once
#include "Tile.h"
#include <string>
#define RSIZEX 8
#define RSIZEY 6
class Room:public Tilemap
{
	weak_ptr<Area> areas[RSIZEX][RSIZEY];
public:
	
	Room() {

	}
	void f1() {
		for (int i = 0; i < RSIZEX; i++)
		{
			for (int j = 0; j < RSIZEY; j++)
			{
				areas[i][j] = Instantiate<Area>("Area");
				areas[i][j].lock()->GetTransform()->SetParent(transform->wp, Vector2i(i-RSIZEX/2, j-RSIZEY/2));
					if ((i + j) % 2)
						areas[i][j].lock()->GetTransform()->renderBox.setFillColor(Color::Magenta);
					else
						areas[i][j].lock()->GetTransform()->renderBox.setFillColor(Color::Black);
				areas[i][j].lock()->GetTransform()->SetSize(GetTransform()->GetAreaSize(), BoxType::RenderBox);
			}
		}
	}
	Room(std::string s) :Tilemap(s){}
};


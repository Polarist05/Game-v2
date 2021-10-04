#include "GameSprite.h"
#include "WorldControl.h"
#include <iostream>
#include <stdio.h>
#include "Player.h"
#include "Collision.h"
#include "Tile.h"
#include "Room.h"
#include "GameRenderer.h"
#include "Dungeon.h"
using namespace sf;
using namespace std;
void ActivateStart();
void ActivateUpdate();
void KeyHold();
class a1 :public GameSprite {
public:
	a1(std::string s) :GameSprite(s) {}
};
int main() {
	auto seed = time(NULL);
	srand(seed);
	WControl::SetUsedRoomPrefab();
	for (map<std::string, Texture>::iterator it = WControl::objectsPrefab().begin(); it != WControl::objectsPrefab().end(); it++)
	{
		std::cout << it->first << endl;
	}
	Dungeon dungeon;
	GameRenderer gameRenderer;
	WorldControl::isGamePlaying() = true;
	WorldControl::window().setFramerateLimit(60);
	WorldControl::window().setKeyRepeatEnabled(false);
	ActivateStart();
	while (WorldControl::window().isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::J))
			std::cout << seed <<" " << endl;
		WorldControl::window().clear(sf::Color::Red);
		sf::Event event;
		while (WorldControl::window().pollEvent(event))
		{
			// "close requested" event: we close the
			if (event.type == Event::Closed)
				WorldControl::window().close();
		}
		WControl::view().setCenter(WControl::getMainDungeon().Rooms[WControl::GetCurrentRoom().y][WControl::GetCurrentRoom().x].lock()->MiddlePositionOfRoom());
		//WControl::view().setCenter(WorldControl::player().lock()->transform->renderBox.getPosition());
		WorldControl::window().setView(WControl::view());
		MoveAllSprites(WorldControl::Hierarchy(), 0, Vector2f(0, 0), Vector2f(1, 1));
		gameRenderer.RenderAll();
		KeyHold();
		ActivateUpdate();
		WorldControl::window().display();
		
	}
	std::cout << endl << "end program" << endl;
}

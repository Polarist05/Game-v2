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
void ActivateUpdate();
void KeyHold();
class a1 :public GameSprite {
public:
	a1(std::string s) :GameSprite(s) {}
};
int main() {
	auto seed = time(NULL);
	srand(1633453637);
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
		WorldControl::window().setView(WControl::view());
		MoveAllSprites(WorldControl::Hierarchy(), 0, Vector2f(0, 0), Vector2f(1, 1));
		KeyHold();
		ActivateUpdate();
		gameRenderer.RenderAll();
		
		
		WorldControl::window().display();
		
	}
	std::cout << endl << "end program" << endl;
}

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
void CheckAllSpriteName(weak_ptr<GameSprite> a, int b);
int main() {
	auto seed = time(NULL);
	srand(seed);
	WControl::SetUsedRoomPrefab();
	Dungeon dungeon;
	GameRenderer gameRenderer;
	WorldControl::window().setFramerateLimit(60);
	WorldControl::window().setKeyRepeatEnabled(false);
	while (WorldControl::window().isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::J)) {
			std::cout << seed << " " << endl;
			CheckAllSpriteName(WControl::Hierarchy(),0);
		}
		WorldControl::window().clear(sf::Color::Red);
		sf::Event event;
		while (WorldControl::window().pollEvent(event))
		{
			if (event.type == Event::Closed)
				WorldControl::window().close();
		}
		WorldControl::window().setView(WControl::view());
		Mode::currentMode().lock()->CheckKeyPress();
		MoveAllSprites(WorldControl::Hierarchy(), 0, Vector2f(0, 0));
		Mode::currentMode().lock()->Update();
		Mode::currentMode().lock()->RenderGame();
		//gameRenderer.RenderAll();
		WorldControl::window().display();
		
	}
	std::cout << endl << "end program" << endl;
}

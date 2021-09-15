#pragma once
#pragma once
#include "SFML.h"
#include "GameBaseClass.h"
#include "GameSprite.h"
#include "Tile.h"
#include "Player.h"
class WorldControl:public GameBaseClass {
public:
	static RenderWindow& window();
	static float WorldScale();
	static weak_ptr<GameSprite> NotrenderSprite();
	static weak_ptr<Tilemap> NotrenderTilemap();
	static weak_ptr<Tile> MainTile();
	static weak_ptr<GameSprite> Hierarchy();
	static weak_ptr<Tile> NotrenderTile();
	static weak_ptr<Player> player();
	WorldControl() {
		NotrenderTile().lock()->transform->SetParent(NotrenderSprite());
		MainTile().lock()->transform->position = Vector2f(0, 0);
		MainTile().lock()->SetAreaSize(Vector2f(190, 140));
	}
};
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
	static weak_ptr<GameSprite> Hierarchy();
	static weak_ptr<Tile> NotrenderTile();
	weak_ptr<Tilemap> NotrenderTilemap();
	static weak_ptr<Player> player();
	void Start()override
	{
		NotrenderTile().lock()->transform->SetParent(NotrenderSprite());
	}
};
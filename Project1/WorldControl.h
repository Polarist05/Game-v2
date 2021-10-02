#pragma once
#pragma once
#include "SFML.h"
#include "GameBaseClass.h"
#include "GameSprite.h"
#include "Tile.h"
#include "Player.h"
#include "Dungeon.h"
#define WControl WorldControl
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
	static map<std::string, pair<bool,vector< RoomData > > >& allRoomPrefabs();
	static map< RoomType, vector< RoomData > >& usedRoomPrefabs();
	static void SetMainDungeon(Dungeon* MainDungeon);
	static Dungeon& getMainDungeon();
	static bool& isGamePlaying();
	static Vector2i& GetCurrentRoom();
	static void SetCurrentRoom(const Vector2i& currentRoom);
	WorldControl() {
		NotrenderTile().lock()->transform->SetParent(NotrenderSprite());
		MainTile().lock()->transform->position = Vector2f(0, 0);
		MainTile().lock()->SetAreaSize(Vector2f(190, 140));
	}
};
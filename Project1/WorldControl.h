#pragma once
#pragma once
#include "SFML.h"
#include "GameBaseClass.h"
#include "GameSprite.h"
#include "Tile.h"
#include "Player.h"
#include "Dungeon.h"
#define WControl WorldControl
#define AREA_SIZEX 190
#define AREA_SIZEY 140
class WorldControl:public GameBaseClass {
	static void LoadData();
	static void LoadAllRoomPrefab();
	static void LoadAllObjectPrefab();
	static void LoadPlayerPerfab();
public:
	//local variable
	static RenderWindow& window();
	static float WorldScale();
	static weak_ptr<GameSprite> NotrenderSprite();
	static weak_ptr<Tilemap> NotrenderTilemap();
	static weak_ptr<Tile> MainTile();
	static weak_ptr<GameSprite> Hierarchy();
	static weak_ptr<Tile> NotrenderTile();
	static weak_ptr<Player> player();
	static map<std::string, pair<pair<bool, bool>,vector< RoomData > > >& allRoomPrefabs();
	static map< RoomType, vector< RoomData > >& usedRoomPrefabs();
	static map<std::string, Texture>& objectsPrefab();
	static Dungeon& getMainDungeon();
	static bool& isGamePlaying();
	static Vector2i& GetCurrentRoom();
	static Texture* playerPrefab();
	//Set
	static void SetCurrentRoom(const Vector2i& currentRoom);
	static void SetMainDungeon(Dungeon* MainDungeon);
	//
	static void SaveAllRoomPrefab();
	static void SetUsedRoomPrefab();
	
	static View& view();
	WorldControl() {
		LoadData();
		NotrenderTile().lock()->transform->SetParent(NotrenderSprite());
		MainTile().lock()->transform->position = Vector2f(0, 0);
		MainTile().lock()->SetAreaSize(Vector2f(AREA_SIZEX, AREA_SIZEY));
		Room::SetObjectTypeString();
	}
};
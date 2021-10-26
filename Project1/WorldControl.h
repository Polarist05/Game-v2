#pragma once
#pragma once
#include "SFML.h"
#include "GameBaseClass.h"
#include "GameSprite.h"
#include "Tile.h"
#include "Player.h"
#include "Dungeon.h"
#include <stack>
#include "UI.h"
#include "UX.h"
#define WControl WorldControl
#define AREA_SIZEX 190
#define AREA_SIZEY 140
#define SOUL_AMOUNT 4
#define KEY_AMOUNT 3
class WorldControl:public GameBaseClass {
	static void LoadData();
	static void LoadAllRoomPrefab();
	static void LoadAllObjectPrefab();
	static void LoadPlayerPerfab();
	static void LoadOtherPrefab();
	static void LoadAllASCII();
	static void LoadAllUI();
public:
	//local variable
	static RenderWindow& window();
	static float WorldScale();
	
	static weak_ptr<GameSprite> NotrenderSprite();
	static weak_ptr<Tilemap> NotrenderTilemap();
	static weak_ptr<Tile> MainTile();
	static weak_ptr<Tile> NotrenderTile();

	static weak_ptr<GameSprite> Hierarchy();
	static weak_ptr<GameSprite> UIHierarchy();
	
	static UX& GetUX();
	static weak_ptr<Player> player();
	static weak_ptr<ClickableSprite>& clickableSpriteAtCursor();
	
	static map<std::string, pair<pair<bool, bool>,vector< RoomData > > >& allRoomPrefabs();	
	static map<char, Texture>& ASCIIPrefab();
	static map<std::string, Texture>& objectsPrefab();
	static map<std::string, Texture>& otherPrefab();
	static Texture* playerPrefab();

	static map< RoomType, vector< RoomData > >& usedRoomPrefabs();
	
	static Dungeon& getMainDungeon();
	static bool& isGamePlaying();
	
	static std::stack<UIType>& UIStack();
	static map<UIType, UI*>& AllUI();
	
	static weak_ptr<Room> GetCurrentRoom();
	static Vector2i& GetCurrentRoomPosition();
	static void SetCurrentRoomPositon(const Vector2i& currentRoom);
	
	static void SetMainDungeon(Dungeon* MainDungeon);
	static void SaveAllRoomPrefab();
	static void SetUsedRoomPrefab();
	static void RefreshRoomPrefrab();

	static weak_ptr<ClickableSprite> HoldItem();
	
	static View& view();
	static void SetViewPosition(Vector2f pos);

	WorldControl() {
		LoadData();
		NotrenderTile().lock()->transform->SetParent(NotrenderSprite());
		MainTile().lock()->transform->position = Vector2f(0, 0);
		MainTile().lock()->SetAreaSize(Vector2f(AREA_SIZEX, AREA_SIZEY));
		Room::SetObjectTypeString();
		UIStack().push(UIType::StartPage);
	}
};
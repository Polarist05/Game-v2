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
#include "Load.h"

#include "GameMode.h"
#include "MainMenuMode.h"
#include "PlayMode.h"
#include "ToolkitMode.h"
#include "EndGameMode.h"

#include "StartUI.h"
#include "ToolkitUI.h"
#include "EndGameUI.h"

#define WControl WorldControl
#define AREA_SIZEX 190
#define AREA_SIZEY 140
#define SOUL_AMOUNT 3
#define KEY_AMOUNT 3
#define VIEW_SIZE 1

class WorldControl:public GameBaseClass {

public:
	//local variable
	static RenderWindow& window();
	static float WorldScale();

	static SpriteOffsetData& NormalButtonOffsetData();
	static SpriteOffsetData& TextOffsetData();
	
	static weak_ptr<GameSprite> NotrenderSprite();
	static weak_ptr<Tilemap> NotrenderTilemap();
	static weak_ptr<Tile> MainTile();
	static weak_ptr<Tile> NotrenderTile();

	static weak_ptr<GameSprite> Hierarchy();
	static weak_ptr<GameSprite> UIHierarchy();
	
	static weak_ptr<UX>& GetUX();
	static weak_ptr<Player> player();
	static weak_ptr<ClickableSprite>& clickableSpriteAtCursor();
	
	static map<std::string, pair<pair<bool, bool>,vector< RoomData > > >& allRoomPrefabs();	
	static RoomData& emptyRoom();
	static map<char, Texture>& ASCIIPrefab();
	static map<std::string, Texture>& objectsPrefab();
	static map<std::string, Texture>& otherPrefab();
	static Texture* playerPrefab();

	static map< RoomType, vector< RoomData > >& usedRoomPrefabs();
	
	static void setMainDungeon(Dungeon* dungeon);
	static Dungeon& getMainDungeon();
	
	static std::stack<UIType>& UIStack();
	
	static weak_ptr<Room> GetCurrentRoom();
	static Vector2i& GetCurrentRoomPosition();
	static void SetCurrentRoomPositon(const Vector2i& currentRoom);
	
	static void SetUsedRoomPrefab();

	static weak_ptr<ClickableSprite> HoldItem();
	
	static View& view();
	static void SetViewPosition(Vector2f pos);

	static const Vector2f& GetCursurPosition();
	static map<int,set<int>>& GetChosedAreaPosition();

	static std::string& playerName();
	static std::array<pair<string, int>, 5>& scoreboard();

	WorldControl() {
		Room::SetObjectTypeString();
		Load::LoadData();
		NotrenderTile().lock()->transform->SetParent(NotrenderSprite());
		MainTile().lock()->transform->position = Vector2f(0, 0);
		UIStack().push(UIType::StartPage);
	}
};

namespace Mode {
	shared_ptr<MainMenuMode> mainMenuMode();
	shared_ptr<PlayMode> playMode();
	shared_ptr <ToolkitMode>  toolkitMode();
	shared_ptr <EndGameMode>  endGameMode();
	weak_ptr<GameMode>& currentMode();
	bool CurrentModeIs(weak_ptr<GameMode> gamemode);
}
namespace MyColor {
	Color gray();
}

namespace ALLUI {
	StartUI& startUI();
	ToolkitUI& toolkitUI();
	EndGameUI& endGameUI();
	UI* GetUI(const UIType& UItype);
}
#include "WorldControl.h"
#include "GameRenderer.h"
#include<map>
#include<vector>
#include <iostream>
#include <random>

bool CurrentModeIs(weak_ptr<GameMode> gamemode) {
	return currentMode().lock() == gamemode.lock();
}

using namespace std;

float worldScale = (float)0.7;
float WorldControl::WorldScale() { return worldScale; };
RenderWindow _window(VideoMode((int)(1920. * WorldControl::WorldScale()), (int)(1080. * WorldControl::WorldScale())), "My window");
RenderWindow& WorldControl::window() { return _window; }

View _view(Vector2f(AREA_SIZEX* (RSIZEX + 2)* (2.5), AREA_SIZEY* (RSIZEY + 2) * 2.5) - Vector2f(AREA_SIZEX / 2., AREA_SIZEY / 2.), Vector2f(1920 * VIEW_SIZE, 1080 * VIEW_SIZE));
View& WControl::view() { return _view; }

map<type_index, vector<shared_ptr<GameBaseClass> > > AllEntities;
map<type_index, vector<shared_ptr<GameBaseClass> > >& GetAllEntities() { return AllEntities; }

shared_ptr<MainMenuMode> _mainMenuMode = Instantiate<MainMenuMode>().lock();
shared_ptr<PlayMode> _playMode = Instantiate<PlayMode>().lock();
shared_ptr <ToolkitMode>  _toolkitMode = Instantiate<ToolkitMode>().lock();
weak_ptr<GameMode> _currentMode = _mainMenuMode;
shared_ptr<MainMenuMode> mainMenuMode() { return _mainMenuMode; }
shared_ptr<PlayMode> playMode() { return _playMode; }
shared_ptr <ToolkitMode>  toolkitMode() { return _toolkitMode; }
weak_ptr<GameMode>& currentMode() { return _currentMode; }

map<std::string, pair<pair<bool, bool>, vector< RoomData > > > _allRoomPrefabs;
map<std::string, pair<pair<bool, bool>, vector< RoomData > > >& WorldControl::allRoomPrefabs() { return _allRoomPrefabs; }
RoomData  _emptyRoom;
RoomData& WorldControl::emptyRoom() { return _emptyRoom; }

map< RoomType, vector< RoomData > > _usedRoomPrefabs;
map< RoomType, vector< RoomData > >& WorldControl::usedRoomPrefabs() { return _usedRoomPrefabs; };

map<char, Texture> _ASCIIPrefab;
map<char, Texture>& WorldControl::ASCIIPrefab() { return _ASCIIPrefab; }

map<std::string, Texture> _objectsPrefab;
map<std::string, Texture>& WorldControl::objectsPrefab() { return _objectsPrefab; };

map<std::string, Texture> _otherPrefab;
map<std::string, Texture>& WorldControl::otherPrefab() { return _otherPrefab; };

SpriteOffsetData _normalButtonOffsetData(Vector2i(0, 0), Vector2i(295, 45), Vector2f(295, 45), Vector2f(0, 0), Vector2f(0, 0), VIEW_SIZE);
SpriteOffsetData& WorldControl::NormalButtonOffsetData() { return _normalButtonOffsetData; }
SpriteOffsetData _textOffsetData(Vector2i(0, 0), Vector2i(20, 45), Vector2f(20, 45), Vector2f(0, 0), Vector2f(0, 0), VIEW_SIZE);
SpriteOffsetData& WorldControl::TextOffsetData() { return _textOffsetData; }

weak_ptr<GameSprite> _notRenderSprite = Instantiate<GameSprite>("NotRenderSprite");
weak_ptr<GameSprite> WorldControl::NotrenderSprite() { return _notRenderSprite; }

weak_ptr<Tile> _notRenderTile = Instantiate<Tile>("NotRenderTile");
weak_ptr<Tile> WorldControl::NotrenderTile() { return _notRenderTile; }

weak_ptr<Tilemap> _notRenderTilemap = Instantiate<Tilemap>("NotRenderTilemap");
weak_ptr<Tilemap> WorldControl::NotrenderTilemap() { return _notRenderTilemap; }

weak_ptr<GameSprite> _hierarchy = Instantiate<GameSprite>("hierarchy");
weak_ptr<GameSprite> WorldControl::Hierarchy() { return _hierarchy; }

weak_ptr<GameSprite> _UIhierarchy = Instantiate<GameSprite>("UIHierarchy");
weak_ptr<GameSprite> WorldControl::UIHierarchy() { return _UIhierarchy; }

weak_ptr<Tile> _RenderTile = Instantiate<Tile>("MainTile");
weak_ptr<Tile> WorldControl::MainTile() { return _RenderTile; }

Dungeon* _MainDungeon;
void WorldControl::setMainDungeon(Dungeon* dungeon) { _MainDungeon = dungeon; }
Dungeon& WorldControl::getMainDungeon() { return *_MainDungeon; }

weak_ptr<UX> _UX =Instantiate<UX>();
weak_ptr<UX>& WControl::GetUX() { return _UX; }

weak_ptr<Player> _player = Instantiate<Player>("player");
weak_ptr<Player> WorldControl::player() { return _player; }
weak_ptr<ClickableSprite> _clickableSpriteAtCursor;
weak_ptr<ClickableSprite>& WControl::clickableSpriteAtCursor() { return _clickableSpriteAtCursor; };

/*bool _isGamePlaying = false;
bool& WorldControl::isGamePlaying() { return _isGamePlaying; };*/


std::stack<UIType> _UIStack;
std::stack<UIType>& WorldControl::UIStack() { return _UIStack; }

map<UIType, UI*> _AllUI;
map<UIType, UI*>& WorldControl::AllUI() { return _AllUI; }

weak_ptr<ClickableSprite> _HoldItem;
weak_ptr<ClickableSprite> WorldControl::HoldItem() { return _HoldItem; }

Vector2i _currentRoom;
weak_ptr<Room> WorldControl::GetCurrentRoom() { return getMainDungeon().Rooms[GetCurrentRoomPosition().y][GetCurrentRoomPosition().x]; }
Vector2i& WorldControl::GetCurrentRoomPosition() { return _currentRoom; }
void WorldControl::SetCurrentRoomPositon(const Vector2i& currentRoom) {
	_currentRoom = currentRoom;
	SetViewPosition(WControl::GetCurrentRoom().lock()->MiddlePositionOfRoom());
}

void WControl::SetViewPosition(Vector2f pos) {
	WControl::view().setCenter(WControl::GetCurrentRoom().lock()->MiddlePositionOfRoom());
	WControl::UIHierarchy().lock()->transform->SetPosition(WControl::GetCurrentRoom().lock()->MiddlePositionOfRoom());
}

Texture _playerPrefab;
Texture* WorldControl::playerPrefab() { return &_playerPrefab; }

void WorldControl::SetUsedRoomPrefab() {
	WorldControl::usedRoomPrefabs().clear();
	for (auto& it :WorldControl::allRoomPrefabs()) {
		if (it.second.first.first && !it.second.first.second) {
			for (int i = 0; i < it.second.second.size(); i++) {
				WorldControl::usedRoomPrefabs()[it.second.second[i].roomType].push_back(it.second.second[i]);
			}
		}
	}
	for (int i = 1; i <= 13;i++ ) {
		if (WorldControl::usedRoomPrefabs()[(RoomType)i].empty())
			printf("You dont add all room type\n");
	}
}

const Vector2f& WorldControl::GetCursurPosition() {
	Vector2f cursurPos = view().getCenter() - Multiple(view().getSize(), Vector2f(0.5, 0.5));
	cursurPos += Multiple(Vector2f(1 / WorldScale(), 1 / WorldScale()), (Vector2f)Mouse::getPosition(WControl::window()));
	return cursurPos;
}

static map<int, set<int>> _chosedAreaPosition;
map<int, set<int>>& WorldControl::GetChosedAreaPosition() {return _chosedAreaPosition;}

//for.h file
RenderWindow& Player::window() { return _window; }
RenderWindow& GameRenderer::window() { return _window; }
weak_ptr<GameSprite> GameRenderer::player() { return _player; }
weak_ptr<GameSprite> GameSprite::GameTransform::Hierachy() { return _hierarchy; }
weak_ptr<GameSprite>GameRenderer::Hierachy() { return _hierarchy; }
weak_ptr<Tile> Tilemap::TilemapTransform::NotrenderTile() { return _notRenderTile; }
weak_ptr<Tilemap> Area::AreaTransform::NotrenderTilemap() { return _notRenderTilemap; }
weak_ptr<WorldControl> WorldControlInstant = Instantiate<WorldControl>();

Vector2f Multiple(const Vector2f& a, const Vector2f& b) { return Vector2f(a.x * b.x, a.y * b.y); }
Vector2f Multiple(const Vector2f& a, const Vector2f& b, const Vector2f& c) { return Vector2f(a.x * b.x * c.x, a.y * b.y * c.y); }
Vector2f Flip(const Vector2f& a) { return Vector2f(a.y, a.x); }
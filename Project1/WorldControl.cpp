#include "WorldControl.h"
#include "GameRenderer.h"
#include<map>
#include<vector>
using namespace std;
float worldScale = (float)0.7;
float WorldControl::WorldScale() { return worldScale; };
RenderWindow _window(VideoMode((int)(1920. * WorldControl::WorldScale()), (int)(1080. * WorldControl::WorldScale())), "My window");
RenderWindow& WorldControl::window() { return _window; }
map<type_index, vector<shared_ptr<GameBaseClass> > > AllEntities;
map<type_index, vector<shared_ptr<GameBaseClass> > >& GetAllEntities() { return AllEntities; }

map<std::string, pair<bool, vector< RoomData > > > _allRoomPrefabs;
map<std::string, pair<bool, vector< RoomData > > >& WorldControl::allRoomPrefabs() { return _allRoomPrefabs; }

map< RoomType ,vector< RoomData > > _usedRoomPrefabs;
map< RoomType, vector< RoomData > >& WorldControl::usedRoomPrefabs() { return _usedRoomPrefabs; };

weak_ptr<GameSprite> _notRenderSprite = Instantiate<GameSprite>("NotRenderSprite");
weak_ptr<GameSprite> WorldControl::NotrenderSprite() { return _notRenderSprite; }

weak_ptr<Tile> _notRenderTile = Instantiate<Tile>("NotRenderTile");
weak_ptr<Tile> WorldControl::NotrenderTile() { return _notRenderTile; }

weak_ptr<Tilemap> _notRenderTilemap = Instantiate<Tilemap>("NotRenderTilemap");
weak_ptr<Tilemap> WorldControl::NotrenderTilemap() { return _notRenderTilemap; }

weak_ptr<GameSprite> _hierarchy = Instantiate<GameSprite>("hierarchy");
weak_ptr<GameSprite> WorldControl::Hierarchy() { return _hierarchy; }

weak_ptr<Tile> _RenderTile = Instantiate<Tile>("MainTile");
weak_ptr<Tile> WorldControl::MainTile() { return _RenderTile; }

Dungeon* _MainDungeon;
void WorldControl::SetMainDungeon(Dungeon* MainDungeon) { _MainDungeon = MainDungeon; }
Dungeon& WorldControl::getMainDungeon() { return *_MainDungeon; }

weak_ptr<Player> _player=Instantiate<Player>("player");
weak_ptr<Player> WorldControl::player() { return _player; }

bool _isGamePlaying = false;
bool& WorldControl::isGamePlaying() { return _isGamePlaying; };

Vector2i _currentRoom;
Vector2i& WorldControl::GetCurrentRoom() { return _currentRoom; }
void WorldControl::SetCurrentRoom(const Vector2i& currentRoom) { _currentRoom = currentRoom; }

//for.h file
RenderWindow& Player::window() { return _window; }
RenderWindow& GameRenderer::window() { return _window; }
weak_ptr<GameSprite> GameRenderer::player() { return _player; }
weak_ptr<GameSprite> GameSprite::GameTransform::Hierachy() { return _hierarchy; }
weak_ptr<GameSprite>GameRenderer::Hierachy() { return _hierarchy; }
weak_ptr<Tile> Tilemap::TilemapTransform::NotrenderTile() { return _notRenderTile; }
weak_ptr<Tilemap> Area::AreaTransform::NotrenderTilemap() { return _notRenderTilemap; }
weak_ptr<WorldControl> WorldControlInstant = Instantiate<WorldControl>();
/*bool& Room::isGamePlaying() { return _isGamePlaying; };
Dungeon& Room::getMainDungeon() { return *_MainDungeon; }
Vector2i& Room::GetCurrentRoom() { return _currentRoom; }*/

Vector2f Multiple(const Vector2f& a, const Vector2f& b) { return Vector2f(a.x * b.x, a.y * b.y); }
Vector2f Multiple(const Vector2f& a, const Vector2f& b, const Vector2f& c) { return Vector2f(a.x * b.x * c.x, a.y * b.y * c.y); }
Vector2f Flip(const Vector2f& a) { return Vector2f(a.y, a.x); }
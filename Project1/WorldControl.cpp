#include "WorldControl.h"
#include<map>
#include<vector>
using namespace std;
float worldScale = (float)0.9;
float WorldControl::WorldScale() { return worldScale; };
RenderWindow _window(VideoMode((int)(1920. * WorldControl::WorldScale()), (int)(1080. * WorldControl::WorldScale())), "My window");
RenderWindow& WorldControl::window() { return _window; }
map<type_index, vector<shared_ptr<GameBaseClass> > > AllEntities;
map<type_index, vector<shared_ptr<GameBaseClass> > >& GetAllEntities() { return AllEntities; }
weak_ptr<WorldControl> Instant = Instantiate<WorldControl>();
//gameSprite
weak_ptr<GameSprite> _notRenderSprite = Instantiate<GameSprite>("Not render sprite");
weak_ptr<GameSprite> WorldControl::NotrenderSprite() { return _notRenderSprite; }
weak_ptr<GameSprite> _hierarchy = Instantiate<GameSprite>("hierarchy");
weak_ptr<GameSprite> WorldControl::Hierarchy() { return _hierarchy; }
weak_ptr<Tile> _notRenderTile = Instantiate<Tile>();
weak_ptr<Tile> WorldControl::NotrenderTile() { return _notRenderTile; }
weak_ptr<Tilemap> _notRenderTilemap = Instantiate<Tilemap>();
weak_ptr<Tilemap> WorldControl::NotrenderTilemap() { return _notRenderTilemap; }
weak_ptr<Player> _player = Instantiate<Player>("player");
weak_ptr<Player> WorldControl::player() { return _player; }
//for.h file
RenderWindow& Player::window() { return _window; }
weak_ptr<GameSprite> GameSprite::GameTransform::Hierachy() { return _hierarchy; }
weak_ptr<Tile> Tilemap::TilemapTransform::NotrenderTile() { return _notRenderTile; }
weak_ptr<Tilemap> Area::AreaTransform::NotrenderTilemap() { return _notRenderTilemap; }
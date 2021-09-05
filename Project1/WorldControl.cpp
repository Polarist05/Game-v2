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
weak_ptr<GameSprite> _hierarchy;
weak_ptr<GameSprite>& f1() { return _hierarchy; }
weak_ptr<GameSprite> GameTransform::Hierachy() { return _hierarchy; }
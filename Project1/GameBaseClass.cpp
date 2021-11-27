#include "GameBaseClass.h"
#include "GameSprite.h"
#include<queue>
using namespace std;
void Destroy(weak_ptr<GameBaseClass> _wp, type_index typeIndex) {

	if (_wp.expired()) { printf("This entity is null or expired\n"); return; }
	vector<shared_ptr<GameBaseClass> > ::iterator it = find(GetAllEntities()[typeIndex].begin(), GetAllEntities()[typeIndex].end(), _wp.lock());
	if (it == GetAllEntities()[typeIndex].end()) { printf(" Cant find that entity error please check your code\n"); }
	else {
		GetAllEntities()[typeIndex].erase(it);
		if (!_wp.expired()) { printf("It have left some share_ptr somewhere after destroy entity please check your code\n"); }
	}
}

void GameBaseClass::Start(){}
void GameBaseClass::Update(){}

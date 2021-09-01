#pragma once
#include<memory>
#include<typeinfo>
#include <map>
#include <vector>
#include<typeindex>
using namespace std;
class SubClass {
public:
	virtual void Start() {}
	virtual void Update() {}
};
class  GameBaseClass :public SubClass {
public:

};
void PushQStart(weak_ptr<GameBaseClass> _a);
void PushQUpdate(weak_ptr<GameBaseClass> _a);
map<type_index, vector<shared_ptr<GameBaseClass> > >& GetAllEntities();
//class GameSprite;
//class GameTransform;
template <typename T>
weak_ptr<T> Instantiate() {
	shared_ptr<GameBaseClass> sp = make_shared<T>();
	GetAllEntities()[type_index(typeid(T))].push_back(sp);
	PushQUpdate(sp);
	PushQStart(sp);
	//weak_ptr<GameSprite> wp = dynamic_pointer_cast<GameSprite>(sp);
	//if (!wp.expired()) {
	//	wp.lock()->transform = GameTransform(wp, type_index(typeid(T)));
	//	//must not use GameTransform(sp)
	//	printf("1***\n");
	//}
	//else {
	//	printf("0***\n");
	//}
	return dynamic_pointer_cast<T>(sp);
}
template <typename T>
void Destroy(weak_ptr<T> _wp) {

	if (_wp.expired()) {printf("This entity is null or expired\n");return;}
	vector<shared_ptr<GameBaseClass> > ::iterator it=find(GetAllEntities()[type_index(typeid(T))].begin(), GetAllEntities()[type_index(typeid(T))].end(),_wp.lock());
	if (it == GetAllEntities()[type_index(typeid(T))].end()) { printf(" Cant find that entity error please check your code\n"); }
	else {
		GetAllEntities()[type_index(typeid(T))].erase(it);
		if (!_wp.expired()) { printf("It have left some share_ptr somewhere after destroy entity please check your code"); }
	}
}
void Destroy(weak_ptr<GameBaseClass> _wp, type_index typeIndex);
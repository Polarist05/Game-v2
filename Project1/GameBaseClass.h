#pragma once
#include<memory>
#include<typeinfo>
#include <map>
#include <vector>
#include<typeindex>
#include <string>
using namespace std;
class GameSprite;
void SetGameSprite(weak_ptr<GameSprite> wp, type_index t);
class  GameBaseClass{
public:
	virtual void Start() ;
	virtual void Update() ;
};
map<type_index, vector<shared_ptr<GameBaseClass> > >& GetAllEntities();
template <typename T>
weak_ptr<T> Instantiate() {
	type_index t = type_index(typeid(T));
	shared_ptr<GameBaseClass> sp = make_shared<T>();
	GetAllEntities()[t].push_back(sp);
	weak_ptr < GameSprite > wp = dynamic_pointer_cast<GameSprite>(sp);
	if (!wp.expired()) {
		SetGameSprite(wp, t);
	}
	sp->Start();
	return dynamic_pointer_cast<T>(sp);
}
template <typename T>
weak_ptr<T> Instantiate(const std::string s) {
	type_index t = type_index(typeid(T));
	shared_ptr<GameBaseClass> sp = make_shared<T>(s);
	GetAllEntities()[t].push_back(sp);
	weak_ptr < GameSprite > wp = dynamic_pointer_cast<GameSprite>(sp);
	if (!wp.expired())
		SetGameSprite(wp, t);
	sp->Start();
	return dynamic_pointer_cast<T>(sp);
}
template <typename T>
void Destroy(weak_ptr<T> _wp) {

	if (_wp.expired()) {printf("This entity is null or expired\n");return;}
	vector<shared_ptr<GameBaseClass> > ::iterator it=find(GetAllEntities()[type_index(typeid(T))].begin(), GetAllEntities()[type_index(typeid(T))].end(),_wp.lock());
	if (it == GetAllEntities()[type_index(typeid(T))].end()) { printf(" Cant find that entity error please check your code\n"); }
	else {
		GetAllEntities()[type_index(typeid(T))].erase(it);
		if (!_wp.expired()) { printf("It have left some share_ptr somewhere after destroy entity please check your code\n"); }
	}
}
void Destroy(weak_ptr<GameBaseClass> _wp, type_index typeIndex);
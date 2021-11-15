#include "NormalBlockClass.h"
NormalBlockClass::NormalBlockClass():Area(){}
NormalBlockClass::NormalBlockClass(std::string s):Area(s){}

void NormalBlockClass::interacting(weak_ptr<Knife> knife) {
	Vector2f newPos = knife.lock()->transform->GetRealposition()-transform->GetRealposition();
	knife.lock()->transform->position = newPos;
	knife.lock()->transform->SetParent(transform->wp);
	
	knife.lock()->Stop();
}



#include "NormalBlockClass.h"
NormalBlockClass::NormalBlockClass():Area(){}
NormalBlockClass::NormalBlockClass(std::string s):Area(s){}

void NormalBlockClass::interacting(weak_ptr<Knife> knife) {
	knife.lock()->Stop();
}



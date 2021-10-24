#include "DeleteBlockClass.h"

DeleteBlockClass::DeleteBlockClass():Area(){}
DeleteBlockClass::DeleteBlockClass(std::string s):Area(s){}

void DeleteBlockClass::interacting(weak_ptr<Knife> knife){
	Destroy(knife);
}

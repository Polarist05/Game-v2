#include "ChargeSoulClass.h"
#include "WorldControl.h"
ChargeSoulClass::ChargeSoulClass(std::string s) :Area(s) {};
ChargeSoulClass::ChargeSoulClass() :Area() {};

void ChargeSoulClass::MeleeAttackActivate() {
	if (!wasUsed) {
		WControl::player().lock()->IncreaseSoul(1);
		wasUsed = true;
	}
}
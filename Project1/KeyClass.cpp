#include "KeyClass.h"
#include "WorldControl.h"
void KeyClass::WalkThroughActivate() {
	WControl::player().lock()->IncreaseKey(1);
	WControl::player().lock()->IncreaseScore(200);
	WControl::GetCurrentRoom().lock()->cannotPush[GetTransform()->GetPositionInTilemap().y][GetTransform()->GetPositionInTilemap().x] = false;
	Destroy(GetTransform()->wp, GetTransform()->typeIndex);
}
KeyClass::KeyClass() :Area() {};
KeyClass::KeyClass(std::string s) :Area(s) {}
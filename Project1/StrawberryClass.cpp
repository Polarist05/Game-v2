#include "StrawberryClass.h"
#include "WorldControl.h"
void StrawberryClass::WalkThroughActivate() {
	WControl::sound()["Beep"].play();
	WControl::player().lock()->IncreaseScore(200);
	WControl::GetCurrentRoom().lock()->cannotPush[GetTransform()->GetPositionInTilemap().y][GetTransform()->GetPositionInTilemap().x] = false;
	Destroy(GetTransform()->wp, GetTransform()->typeIndex);
}
StrawberryClass::StrawberryClass() :Area() {};
StrawberryClass::StrawberryClass (std::string s) :Area(s) {}
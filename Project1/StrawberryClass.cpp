#include "StrawberryClass.h"
#include "WorldControl.h"
void StrawberryClass::WalkThroughActivate() {
	WControl::player().lock()->IncreaseScore(200);
	Destroy(GetTransform()->wp, GetTransform()->typeIndex);
}
StrawberryClass::StrawberryClass() :Area() {};
StrawberryClass::StrawberryClass (std::string s) :Area(s) {}
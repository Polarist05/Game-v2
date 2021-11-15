#include "BellClass.h"
#include "WorldControl.h"
BellClass::BellClass() :Input() { };
BellClass::BellClass(std::string s) :Input(s) {};

void BellClass::Start() {
	ringArea.lock()->transform->SetParent(transform->wp);
	ringArea.lock()->transform->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(3, 3)), HitBox);
	ringArea.lock()->transform->hitBox.setFillColor(Color::Transparent);
	ringArea.lock()->transform->RenderPriority = RenderPriorityType::PlayerAndObject;
}
void BellClass::Update() {
	if (isActivate) {
		if (clock()  > StartActivateTime+ RING_DURATION) {
			TurnOn(false);
			isActivate = false;
			ringArea.lock()->transform->hitBox.setFillColor(Color::Transparent);
		}
	}
}
void BellClass::ActivateRinging()
{

	TurnOn(true);
	isActivate = true;
	StartActivateTime = clock();
	ringArea.lock()->transform->hitBox.setFillColor(Color(255, 255, 255, 50));
}
void  BellClass::MeleeAttackActivate() {
	if (!isActivate) {
		ActivateRinging();
	}
}
void BellClass::interacting(weak_ptr<Knife> knife){
	Vector2f newPos = knife.lock()->transform->GetRealposition() - transform->GetRealposition();
	knife.lock()->transform->position = newPos;
	knife.lock()->transform->SetParent(transform->wp);
	knife.lock()->Stop();
	if (!isActivate) {
		ActivateRinging();
	}
}
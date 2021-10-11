#include "BellClass.h"
#include "WorldControl.h"
BellClass::BellClass() :Area() { };
BellClass::BellClass(std::string s) :Area(s) {};

void  BellClass::MeleeAttackActivate() {
	if (!isActivate) {
		isActivate = true;
		StartActivateTime = clock();
		ringArea.lock()->transform->hitBox.setFillColor(Color(255,255,255,50));
		
	}
}
void BellClass::Start() {
	ringArea.lock()->transform->SetParent(transform->wp);
	ringArea.lock()->transform->SetSize(Multiple(WControl::MainTile().lock()->GetAreaSize(), Vector2f(3, 3)), HitBox);
	ringArea.lock()->transform->hitBox.setFillColor(Color::Transparent);
	ringArea.lock()->transform->RenderPriority = RenderPriorityType::PlayerAndObject;
}
void BellClass::Update() {
	if (isActivate) {
		if (clock() - StartActivateTime > RING_DURATION) {
			isActivate = false;
			ringArea.lock()->transform->hitBox.setFillColor(Color::Transparent);
			lastFrameCollisionObjects.clear();
		}
		else
			WControl::GetCurrentRoom().lock()->CheckCollisionRingHitBoxAndMeleeAttackableObject(transform->wp);
	}
}
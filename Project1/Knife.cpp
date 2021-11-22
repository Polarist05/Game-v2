#include "Knife.h"
#include "WorldControl.h"
Knife::Knife(){}
Knife::Knife(std::string s):GameSprite(s){}
const Direction& Knife::GetDirection(){return direction;}
void Knife::Start()
{
	WControl::sound()["Throw"].play();
	direction = WControl::player().lock()->GetPlayerDirection();
	SpriteOffsetData spriteOffset(Vector2i(1, 5), Vector2i(276, 63), Vector2f(276, 63), Vector2f(0, 0), Vector2f(0, 0), float(0.6));
	
	transform->renderBox.setTexture(&WControl::otherPrefab()["Knife"]);
	transform->SetAllSpriteOffset(spriteOffset);
	transform->SetAnchorType(AnchorType::MiddleCentor, HitBox, FIX_ALL_RECT_POSITION);
	transform->SetSize(transform->pseudoRenderBox.getSize() + Vector2f(-30, 0), PseudoRenderBox);
	transform->SetSize(transform->pseudoRenderBox.getSize(), HitBox);
	transform->SetAnchorType(AnchorType::MiddleLeft, PseudoRenderBox, FIX_ALL_RECT_POSITION);
	transform->SetAnchorType(AnchorType::MiddleLeft, HitBox, FIX_ALL_RECT_POSITION);
	transform->SetAnchorType(AnchorType::MiddleLeft, RenderBox, FIX_ALL_RECT_POSITION);
	transform->SetPositionOffset(Vector2f(0, 0), RenderBox);
	transform->SetPositionOffset(Vector2f(0, 0), PseudoRenderBox);
	transform->SetPositionOffset(Vector2f(0, 0), HitBox);
	transform->pseudoRenderBox.setFillColor(Color::Yellow);
	transform->RenderPriority = RenderPriorityType::KnifeType;
	transform->SetPosition(WControl::player().lock()->transform->hitBox.getPosition()+ WControl::player().lock()->OffsetThrowingKnife);
	Vector2f flip(transform->pseudoRenderBox.getSize().y, transform->pseudoRenderBox.getSize().x);
	switch (direction)
	{
	case Up:
		transform->renderBox.setRotation(-90);
		transform->SetSize(flip, HitBox);
		transform->SetSize(flip, PseudoRenderBox);
		transform->SetAnchorType(AnchorType::DownCentor, PseudoRenderBox, FIX_ONLY_ANCHOR_POSITION);
		transform->SetAnchorType(AnchorType::DownCentor, HitBox, FIX_ONLY_ANCHOR_POSITION);
		velocity=Vector2f(0, -THROWING_SPEED);
		break;
	case Down:
		transform->renderBox.setRotation(90);
		transform->SetSize(flip, HitBox);
		transform->SetSize(flip, PseudoRenderBox);
		transform->SetAnchorType(AnchorType::TopCentor, PseudoRenderBox, FIX_ONLY_ANCHOR_POSITION);
		transform->SetAnchorType(AnchorType::TopCentor, HitBox, FIX_ONLY_ANCHOR_POSITION);
		
		transform->Move(Vector2f(0, 30));
		velocity = Vector2f(0, THROWING_SPEED);
		break;
	case Right:
		transform->MoveOffset(Vector2f(0, 20), HitBox);
		velocity = Vector2f( THROWING_SPEED,0);
		break;
	case Left:
		transform->renderBox.setRotation(180);
		transform->SetAnchorType(AnchorType::MiddleRight, PseudoRenderBox, FIX_ONLY_ANCHOR_POSITION);
		transform->SetAnchorType(AnchorType::MiddleRight, HitBox, FIX_ONLY_ANCHOR_POSITION);
		transform->MoveOffset(Vector2f(0, 20), HitBox);
		velocity = Vector2f(-THROWING_SPEED,0);
		break;
	default:
		break;
	}
}

void Knife::Update()
{
	if(!isStop)
		transform->Move(velocity);
}

const bool& Knife::GetIsStop() { return isStop; }

void Knife::Stop()
{
	WControl::sound()["KnifeStop"].play();
	isStop = true;
}



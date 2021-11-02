#include "Knife.h"
#include "WorldControl.h"
Knife::Knife(){}
Knife::Knife(std::string s):GameSprite(s){}
const Direction& Knife::GetDirection(){return direction;}
void Knife::Start()
{
	direction = WControl::player().lock()->GetPlayerDirection();
	SpriteOffsetData spriteOffset(Vector2i(1, 5), Vector2i(276, 63), Vector2f(276, 63), Vector2f(0, 0), Vector2f(0, 0), float(0.6));
	
	transform->renderBox.setTexture(&WControl::otherPrefab()["Knife"]);
	transform->SetAllSpriteOffset(spriteOffset);
	transform->		SetAnchorType(AnchorType::MiddleCentor, HitBox, FIX_ALL_RECT_POSITION);
	transform->SetSize(transform->pseudoRenderBox.getSize() + Vector2f(-60, 0), PseudoRenderBox);
	transform->pseudoRenderBox.setFillColor(Color::Yellow);
	transform->RenderPriority = RenderPriorityType::KnifeType;
	transform->SetPosition(WControl::player().lock()->transform->hitBox.getPosition()+ WControl::player().lock()->OffsetThrowingKnife);
	switch (direction)
	{
	case Up:
		transform->renderBox.setRotation(-90);
		
		transform->SetSize(Vector2f(transform->pseudoRenderBox.getSize().y, transform->pseudoRenderBox.getSize().x), HitBox);
		transform->SetSize(Vector2f(transform->pseudoRenderBox.getSize().y, transform->pseudoRenderBox.getSize().x), PseudoRenderBox);
		
		transform->renderBox.setOrigin(30, transform->renderBox.getOrigin().y);
		transform->hitBox.setOrigin(Vector2f(transform->pseudoRenderBox.getOrigin().x, transform->pseudoRenderBox.getSize().y - 30));
		transform->pseudoRenderBox.setOrigin(Vector2f( transform->pseudoRenderBox.getOrigin().x, transform->pseudoRenderBox.getSize().y - 30));
		
		transform->Move(Vector2f(0, WControl::player().lock()->transform->pseudoRenderBox.getSize().y/2-30) );
		velocity=Vector2f(0, -THROWING_SPEED);
		break;
	case Down:
		transform->MoveOffset((Vector2f(0, WControl::player().lock()->transform->renderBox.getSize().y - WControl::player().lock()->transform->renderBox.getOrigin().y - transform->pseudoRenderBox.getOrigin().y)), PseudoRenderBox);
		transform->renderBox.setRotation(90);
		
		transform->SetSize(Vector2f(transform->pseudoRenderBox.getSize().y, transform->pseudoRenderBox.getSize().x), HitBox);
		transform->SetSize(Vector2f(transform->pseudoRenderBox.getSize().y, transform->pseudoRenderBox.getSize().x), PseudoRenderBox);
		
		transform->renderBox.setOrigin(Vector2f(30, transform->renderBox.getOrigin().y));
		transform->hitBox.setOrigin(Vector2f(transform->pseudoRenderBox.getOrigin().x, 30));
		transform->pseudoRenderBox.setOrigin(Vector2f(transform->pseudoRenderBox.getOrigin().x, 30));
		
		transform->Move(Vector2f(0, 30));
		velocity = Vector2f(0, THROWING_SPEED);
		break;
	case Right:
		transform->SetSize(transform->pseudoRenderBox.getSize(), HitBox);
		transform->MoveOffset(-WControl::player().lock()->OffsetThrowingKnife -Vector2f(0,WControl::player().lock()->transform->hitBox.getSize().y / 2), HitBox);
		
		transform->hitBox.setOrigin(Vector2f(30, transform->pseudoRenderBox.getOrigin().y));
		transform->renderBox.setOrigin(Vector2f(30, transform->renderBox.getOrigin().y));
		transform->pseudoRenderBox.setOrigin(Vector2f(30, transform->pseudoRenderBox.getOrigin().y));
		
		transform->Move(Vector2f(WControl::player().lock()->transform->renderBox.getSize().x / 2+ (float)30., 0));
		velocity = Vector2f( THROWING_SPEED,0);
		break;
	case Left:
		transform->SetSize(transform->pseudoRenderBox.getSize(), HitBox);
		transform->MoveOffset(-WControl::player().lock()->OffsetThrowingKnife - Vector2f(0, WControl::player().lock()->transform->hitBox.getSize().y / 2), HitBox);
		
		transform->renderBox.setRotation(180);
		
		transform->hitBox.setOrigin(Vector2f(transform->pseudoRenderBox.getSize().x - 30, transform->pseudoRenderBox.getOrigin().y));
		transform->renderBox.setOrigin(30, transform->renderBox.getOrigin().y);
		transform->pseudoRenderBox.setOrigin(Vector2f(transform->pseudoRenderBox.getSize().x-30, transform->pseudoRenderBox.getOrigin().y));
		
		transform->Move(Vector2f(-WControl::player().lock()->transform->renderBox.getSize().x / 2 - 30., 0));
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
	else if (transform->wp.lock() != WControl::player().lock()->knifes.back().lock()) {
		Destroy(transform->wp, transform->typeIndex);
	}

}

const bool& Knife::GetIsStop() { return isStop; }

void Knife::Stop()
{
	isStop = true;
}



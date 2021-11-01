#include "Player.h"
#include "WorldControl.h"
#include "Collision.h"

Vector2f _endPosition;
Vector2f& Player::EndPosition() { return _endPosition; }
Vector2f _startPosition;
Vector2f& Player::StartPosition() { return _startPosition; }

Player::Player(std::string s) { name = s; transform->RenderPriority = RenderPriorityType::PlayerAndObject; }
void Player::Start() {
	meleeAttackHitbox.lock()->transform->SetParent(transform->wp);
	transform->pseudoRenderBox.setFillColor(Color::Green);
	transform->SetSize(Vector2f(0, 0), BoxType::PseudoRenderBox);
	meleeAttackHitbox.lock()->transform->RenderPriority = RenderPriorityType::PlayerAndObject;
	SetPlayerDirection(Direction::Right);
	meleeAttackHitbox.lock()->transform->hitBox.setFillColor(Color::Transparent);
	hookGuideLine.setFillColor(Color::Transparent);
}
void Player::Update() {
	if (isAttacking && clock()- StartMeleeAttackTime > ATTACK_DURATION) {
		isAttacking = false;
		meleeAttackHitbox.lock()->transform->hitBox.setFillColor(Color::Transparent);
	}
	if (isHooking) {
		if (StartPosition().x > EndPosition().x) {
			if (StartPosition().x - EndPosition().x > HOOKIN_MOVEMENT_X_PER_FRAME) {
				transform->Move(Vector2f(-HOOKIN_MOVEMENT_X_PER_FRAME, 0));
				StartPosition() += Vector2f(-HOOKIN_MOVEMENT_X_PER_FRAME, 0);
			}
			else {
				transform->Move(Vector2f(EndPosition().x - StartPosition().x, 0));
				StartPosition() += Vector2f(-HOOKIN_MOVEMENT_X_PER_FRAME, 0);
				
			}
		}
		else if (StartPosition().x < EndPosition().x) {
			if (EndPosition().x - StartPosition().x > HOOKIN_MOVEMENT_X_PER_FRAME) {
				transform->Move(Vector2f(HOOKIN_MOVEMENT_X_PER_FRAME, 0));
				StartPosition() += Vector2f(HOOKIN_MOVEMENT_X_PER_FRAME, 0);
			}
			else {
				transform->Move(Vector2f(EndPosition().x - StartPosition().x, 0));
				StartPosition() += Vector2f(EndPosition().x - StartPosition().x, 0);
			}
		}
		if (StartPosition().y > EndPosition().y) {
			if (StartPosition().y - EndPosition().y > HOOKIN_MOVEMENT_Y_PER_FRAME) {
				transform->Move(Vector2f(0, -HOOKIN_MOVEMENT_Y_PER_FRAME));
				StartPosition() += Vector2f(0, -HOOKIN_MOVEMENT_Y_PER_FRAME);
			}
			else {
				transform->Move(Vector2f(0, EndPosition().y - StartPosition().y));
				StartPosition() += Vector2f(0, EndPosition().y - StartPosition().y);
			}
		}
		else if (StartPosition().y < EndPosition().y) {
			if (EndPosition().y - StartPosition().y > HOOKIN_MOVEMENT_Y_PER_FRAME) {
				transform->Move(Vector2f(0, HOOKIN_MOVEMENT_Y_PER_FRAME));
				StartPosition() += Vector2f(0, HOOKIN_MOVEMENT_Y_PER_FRAME);
			}
			else {
				transform->Move(Vector2f(0, EndPosition().y - StartPosition().y));
				StartPosition() += Vector2f(0, EndPosition().y - StartPosition().y);
			}
		}
		if (StartPosition() ==  EndPosition()) {
			CancleHooking();
		}
	}
}

void Player::ActivateHooking() { isHooking = true;  }
void Player::CancleHooking() { isHooking = false; printf("1166\n");
}

void Player::SetPlayerDirection(const Direction& direction) {
	if (playerDirection != direction) {
		playerDirection = direction;
		if (playerDirection == Direction::Right) {
			meleeAttackHitbox.lock()->transform->SetSize(Vector2f(100, 150), BoxType::HitBox);
			meleeAttackHitbox.lock()->transform->SetAnchorType(AnchorType::MiddleLeft, HitBox, FIX_ONLY_ANCHOR_POSITION);
			Vector2f v(transform->renderBox.getSize().x - transform->renderBox.getOrigin().x, 0);
			meleeAttackHitbox.lock()->transform->SetPosition(v);
		}
		else if (playerDirection == Direction::Left) {
			meleeAttackHitbox.lock()->transform->SetSize(Vector2f(100, 150), BoxType::HitBox);
			meleeAttackHitbox.lock()->transform->SetAnchorType(AnchorType::MiddleRight, HitBox, FIX_ONLY_ANCHOR_POSITION);
			Vector2f v(-transform->renderBox.getOrigin().x, 0);
			meleeAttackHitbox.lock()->transform->SetPosition(v);
		}
		else if (playerDirection == Direction::Down) {
			meleeAttackHitbox.lock()->transform->SetSize(Vector2f(150, 100), BoxType::HitBox);
			meleeAttackHitbox.lock()->transform->SetAnchorType(AnchorType::TopCentor, HitBox, FIX_ONLY_ANCHOR_POSITION);
			Vector2f v(0,transform->renderBox.getSize().y - transform->renderBox.getOrigin().y);
			meleeAttackHitbox.lock()->transform->SetPosition(v);
		}
		else {
			meleeAttackHitbox.lock()->transform->SetSize(Vector2f(150, 100), BoxType::HitBox);
			meleeAttackHitbox.lock()->transform->SetAnchorType(AnchorType::DownCentor, HitBox, FIX_ONLY_ANCHOR_POSITION);
			Vector2f v(0, -transform->renderBox.getOrigin().y);
			meleeAttackHitbox.lock()->transform->SetPosition(v);
		}
	}
}
const Direction& Player::GetPlayerDirection() { return playerDirection; }
void Player::MeleeAttack() {
	if (!isAttacking) {
		meleeAttackHitbox.lock()->transform->hitBox.setFillColor(Color::Red);
		StartMeleeAttackTime = clock();
		isAttacking = true;
		WControl::GetCurrentRoom().lock()->CheckCollisionBetweenAttackHitBoxAndObject();
	}
}



Vector2f Player::GetRealThrowingPosition()
{
	return transform->hitBox.getPosition()+OffsetThrowingKnife;
}

void Player::ResetSoul() { soul = SOUL_AMOUNT; WControl::GetUX().SetSoul(soul);	}
void Player::IncreaseSoul(int a) { soul += a; if (a > SOUL_AMOUNT) soul = SOUL_AMOUNT; WControl::GetUX().SetSoul(soul);}
void Player::LostSoul(int a) { soul -= a; WControl::GetUX().SetSoul(soul); }
bool Player::HaveSoul(int a) {
	if (soul >= a) return true; else return false;
}

int Player::GetScore() { return score; }
void Player::IncreaseScore(int a) { score += a; }

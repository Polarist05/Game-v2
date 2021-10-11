#include "Player.h"
#include "WorldControl.h"
#include "Collision.h"

Vector2f _lastPosition;
Vector2f& Player::LastPosition() { return _lastPosition; }

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
		if (transform->hitBox.getPosition().x > _lastPosition.x) {
			if (transform->hitBox.getPosition().x - _lastPosition.x > HOOKIN_MOVEMENT_X_PER_FRAME) {
				transform->Move(Vector2f(-HOOKIN_MOVEMENT_X_PER_FRAME, 0));
			}
			else {
				transform->Move(Vector2f(_lastPosition.x - transform->hitBox.getPosition().x, 0));
			}
		}
		else if (transform->hitBox.getPosition().x < _lastPosition.x) {
			if (_lastPosition.x- transform->hitBox.getPosition().x  > HOOKIN_MOVEMENT_X_PER_FRAME)
				transform->Move(Vector2f(HOOKIN_MOVEMENT_X_PER_FRAME, 0));
			else
				transform->Move(Vector2f(_lastPosition.x - transform->hitBox.getPosition().x, 0));
		}
		if (transform->hitBox.getPosition().y > _lastPosition.y) {
			if (transform->hitBox.getPosition().y - _lastPosition.y > HOOKIN_MOVEMENT_Y_PER_FRAME) {
				transform->Move(Vector2f(0, -HOOKIN_MOVEMENT_Y_PER_FRAME));
			}
			else {
				transform->Move(Vector2f(0, _lastPosition.y - transform->hitBox.getPosition().y));
			}
		}
		else if (transform->hitBox.getPosition().y < _lastPosition.y) {
			if (_lastPosition.y - transform->hitBox.getPosition().y > HOOKIN_MOVEMENT_Y_PER_FRAME) {
				transform->Move(Vector2f(0, HOOKIN_MOVEMENT_Y_PER_FRAME));
			}
			else {
				transform->Move(Vector2f(0, _lastPosition.y - transform->hitBox.getPosition().y));
			}
		}
		if (transform->hitBox.getPosition() == _lastPosition) {
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

void Player::IncreaseSoul(int a) { soul += a; if (a > MAX_SOUL) soul = MAX_SOUL; }
void Player::LostSoul(int a) { soul -= a; }
int Player::HaveSoul(int a) {return soul;}

int Player::GetScore() { return score; }
void Player::IncreaseScore(int a) { score += a; }

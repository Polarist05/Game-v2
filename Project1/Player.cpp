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
	if (playerState == e_Attacking || playerState == e_Walking) 
	{
		if (clock()>100+lastChangeTime) 
		{
			if (playerState == e_Attacking) 
			{
				textureIndex = (textureIndex + 1)%5;
				SetTexture(playerState,playerDirection);
			}
			else
			{
				textureIndex = (textureIndex + 1)%6;
				SetTexture(playerState, playerDirection);
			}
		}
	}
	if (playerState == e_Attacking && clock()- StartMeleeAttackTime > ATTACK_DURATION) {
		playerState = e_Stop;
		SetTexture(e_Stop,playerDirection);
		meleeAttackHitbox.lock()->transform->hitBox.setFillColor(Color::Transparent);
	}
	if (playerState == e_Hooking) {
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

void Player::ActivateHooking() { playerState = e_Hooking; WControl::sound()["Wind"].play();}
void Player::CancleHooking() { playerState = e_Stop;}

void Player::SetPlayerDirection(const Direction& direction) {
	if (playerDirection != direction) {
		playerDirection = direction;
		if (playerDirection == Direction::Right) {
			meleeAttackHitbox.lock()->transform->SetSize(Vector2f(55, 150), BoxType::HitBox);
			meleeAttackHitbox.lock()->transform->SetAnchorType(AnchorType::MiddleLeft, HitBox, FIX_ONLY_ANCHOR_POSITION);
			Vector2f v(transform->pseudoRenderBox.getSize().x - transform->pseudoRenderBox.getOrigin().x, 0);
			meleeAttackHitbox.lock()->transform->SetPosition(v + Vector2f(-20, 0));
		}
		else if (playerDirection == Direction::Left) {
			meleeAttackHitbox.lock()->transform->SetSize(Vector2f(55, 150), BoxType::HitBox);
			meleeAttackHitbox.lock()->transform->SetAnchorType(AnchorType::MiddleRight, HitBox, FIX_ONLY_ANCHOR_POSITION);
			Vector2f v(-transform->pseudoRenderBox.getOrigin().x, 0);
			meleeAttackHitbox.lock()->transform->SetPosition(v + Vector2f(20, 0));
		}
		else if (playerDirection == Direction::Down) {
			meleeAttackHitbox.lock()->transform->SetSize(Vector2f(150, 55), BoxType::HitBox);
			meleeAttackHitbox.lock()->transform->SetAnchorType(AnchorType::TopCentor, HitBox, FIX_ONLY_ANCHOR_POSITION);
			Vector2f v(0,transform->pseudoRenderBox.getSize().y - transform->pseudoRenderBox.getOrigin().y);
			meleeAttackHitbox.lock()->transform->SetPosition(v + Vector2f(0, -20));
		}
		else {
			meleeAttackHitbox.lock()->transform->SetSize(Vector2f(150, 55), BoxType::HitBox);
			meleeAttackHitbox.lock()->transform->SetAnchorType(AnchorType::DownCentor, HitBox, FIX_ONLY_ANCHOR_POSITION);
			Vector2f v(0, -transform->pseudoRenderBox.getOrigin().y);
			meleeAttackHitbox.lock()->transform->SetPosition(v+Vector2f(0,20));
		}
	}
}
const Direction& Player::GetPlayerDirection() { return playerDirection; }
void Player::MeleeAttack() {
	if (playerState!=e_Attacking&&playerState!=e_Hooking) 
	{
		WControl::sound()["Attack"].play();
		meleeAttackHitbox.lock()->transform->hitBox.setFillColor(Color::Red);
		StartMeleeAttackTime = clock();
		playerState = e_Attacking;
		textureIndex = 0;
		SetTexture(playerState, playerDirection);
		WControl::GetCurrentRoom().lock()->CheckCollisionBetweenAttackHitBoxAndObject();
	}
}




Vector2f Player::GetRealThrowingPosition()
{
	return transform->hitBox.getPosition()+OffsetThrowingKnife;
}

void Player::ResetSoul() { soul = SOUL_AMOUNT; 	}
void Player::IncreaseSoul(int a) { soul = min(soul+a, SOUL_AMOUNT); }
void Player::Walk(const Vector2f& v)
{
	transform->position += v;
	Direction direction;
	if (v.x > 0) direction = Right;
	else if(v.x < 0) direction = Left;
	else if (v.y > 0) direction = Down;
	else if (v.y < 0) direction = Up;
	else 
	{
		WControl::sound()["FootStep"].stop();
		if (playerState == e_Walking)
		{
			playerState = e_Stop;
			SetTexture(e_Stop, playerDirection);
		}
		return;
	}
	if (WControl::sound()["FootStep"].getStatus() == SoundSource::Status::Stopped&& playerState == e_Walking)
	{
		WControl::sound()["FootStep"].play();
	}
	if (playerState == e_Stop) 
	{
		playerState = e_Walking;
	}
	if(playerState!=e_Attacking)
		SetPlayerDirection(direction);
}
void Player::LostSoul(int a) { soul -= min(a,soul);}
bool Player::HaveSoul(int a) {
	if (soul >= a) return true; else return false;
}
int Player::GetSoul(){return soul;}
int Player::GetScore() { return score; }
void Player::SetTexture(const PlayerState& state, const Direction& direction)
{
	lastChangeTime = clock();
	switch (state)
	{
		int x,y;
	case e_Attacking:
		switch (direction)
		{
		case Up:y = 5; break;
		case Down:y = 4; break;
		case Left:y = 6; break;
		case Right:y = 7; break;
		}
		transform->renderBox.setTextureRect(IntRect(Vector2i(PLAYERSIZE_X * textureIndex, PLAYERSIZE_Y * y), Vector2i(PLAYERSIZE_X, PLAYERSIZE_Y)));
		break;
	case e_Walking:
		
		switch (direction)
		{
		case Up:y = 1; break;
		case Down:y = 0; break;
		case Left:y = 2; break;
		case Right:y = 3; break;
		}
		transform->renderBox.setTextureRect(IntRect(Vector2i(PLAYERSIZE_X * textureIndex, PLAYERSIZE_Y * y), Vector2i(PLAYERSIZE_X, PLAYERSIZE_Y)));
		break;
	case e_Stop:
		switch (direction)
		{
		case Up:y = 1,x=0; break;
		case Down:y = 0,x=0; break;
		case Left:y = 2,x=4; break;
		case Right:y = 3,x=1; break;
		}
		transform->renderBox.setTextureRect(IntRect(Vector2i(PLAYERSIZE_X * x, PLAYERSIZE_Y * y), Vector2i(PLAYERSIZE_X, PLAYERSIZE_Y)));
		break;
	case e_Aiming:
		switch (direction)
		{
		case Up:x = 1; break;
		case Down:x = 0; break;
		case Left:x = 2; break;
		case Right:x = 3; break;
		}
		transform->renderBox.setTextureRect(IntRect(Vector2i(PLAYERSIZE_X * x, PLAYERSIZE_Y * 8), Vector2i(PLAYERSIZE_X, PLAYERSIZE_Y)));
		break;
	case e_Hooking:
		switch (direction)
		{
		case Up:x = 1; break;
		case Down:x = 0; break;
		case Left:x = 2; break;
		case Right:x = 3; break;
		}
		transform->renderBox.setTextureRect(IntRect(Vector2i(PLAYERSIZE_X*x, PLAYERSIZE_Y * 8), Vector2i(PLAYERSIZE_X, PLAYERSIZE_Y)));
		break;
	}
}
void Player::IncreaseScore(int a) { score += a; }
void Player::ResetScore() { score = 0; };

int Player::GetKey(){return key;}
void Player::IncreaseKey(int a) {
	key = std::min(key + a, KEY_AMOUNT);
	if (key == KEY_AMOUNT) {
		Mode::currentMode() = Mode::endGameMode();
		Mode::endGameMode()->SetUp();
	}
}
void Player::ResetKey() { key = 0; }

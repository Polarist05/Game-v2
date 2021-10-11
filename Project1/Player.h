#pragma once
#include "SFML.h"
#include "GameSprite.h"
#include "Dungeon.h"
#define ATTACK_DURATION 800
#define MAX_SOUL 4
#define THROWING_LEVEL 0
#define GUIDELINE_THICKNESS 10
#define HOOKIN_MOVEMENT_X_PER_FRAME 20
#define HOOKIN_MOVEMENT_Y_PER_FRAME 20
class Player :public GameSprite
{
private:
	Direction playerDirection = Direction::Left;
	RenderWindow& window();
	clock_t StartMeleeAttackTime;
	int soul = 0;
	int score = 0;
	Vector2f OffsetThrowingKnife = Vector2f(0, THROWING_LEVEL);
public:
	bool canHook;
	bool isHoldHookButton = false;
	bool isHooking=false;
	Direction HoldingDirection;
	
	Vector2f& LastPosition();
	void ActivateHooking();
	void CancleHooking();

	RectangleShape hookGuideLine;
	RectangleShape lastFrameHitBox;
	weak_ptr<GameSprite>  meleeAttackHitbox = Instantiate<GameSprite>("meleeAttackHitbox");
	
	Vector2f GetRealThrowingPosition();
	
	
	void IncreaseSoul(int a);
	void LostSoul(int a);
	int HaveSoul(int a);
	
	int GetScore();
	void IncreaseScore(int a);

	bool isAttacking=false;

	Player(std::string s);
	void Start() override;
	void SetPlayerDirection(const Direction& direction);
	const Direction& GetPlayerDirection();
	
	void MeleeAttack();
	void Update() override;
	
};
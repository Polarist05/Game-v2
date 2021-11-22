#pragma once
#include "SFML.h"
#include "GameSprite.h"
#include "Dungeon.h"
#include "Knife.h"
#include <queue>
#define ATTACK_DURATION 600
#define THROWING_LEVEL 30
#define GUIDELINE_THICKNESS 10
#define HOOKIN_MOVEMENT_X_PER_FRAME 20
#define HOOKIN_MOVEMENT_Y_PER_FRAME 20
#define PLAYERSIZE_X 178
#define PLAYERSIZE_Y 150
enum PlayerState {
	e_Walking,
	e_Stop,
	e_Aiming,
	e_Hooking,
	e_Attacking
};
class Player :public GameSprite
{
private:
	int textureIndex=0;
	time_t lastChangeTime;
	Direction playerDirection = Direction::Left;
	RenderWindow& window();
	clock_t StartMeleeAttackTime;
	int soul = 0;
	int score = 0;
	int key = 0 ;
public:
	void SetTexture(const PlayerState& state, const Direction& direction);
	PlayerState playerState= e_Stop;
	void Walk(const Vector2f& v);
	Vector2f OffsetThrowingKnife = Vector2f(0, -THROWING_LEVEL);
	queue<weak_ptr<Knife> > knifes;
	bool canHook;
	Direction HoldingDirection;
	
	Vector2f& StartPosition();
	Vector2f& EndPosition();
	void ActivateHooking();
	void CancleHooking();

	RectangleShape hookGuideLine;
	RectangleShape lastFrameHitBox;
	weak_ptr<GameSprite>  meleeAttackHitbox = Instantiate<GameSprite>("meleeAttackHitbox");
	
	Vector2f GetRealThrowingPosition();
	
	int GetSoul();
	void ResetSoul();
	void IncreaseSoul(int a);
	void LostSoul(int a);
	bool HaveSoul(int a);
	
	int GetScore();
	void IncreaseScore(int a);
	void ResetScore();

	int GetKey();
	void IncreaseKey(int a);
	void ResetKey();


	Player(std::string s);
	void Start() override;
	void SetPlayerDirection(const Direction& direction);
	const Direction& GetPlayerDirection();
	
	void MeleeAttack();
	void Update() override;
	
};
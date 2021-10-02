#include "Player.h"
#include "Collision.h"
Player::Player(std::string s) { name = s; transform->RenderPriority = RenderPriorityType::PlayerAndObject; printf("create"); }
void Player::Update() {}
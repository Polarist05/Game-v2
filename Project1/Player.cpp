#include "Player.h"
Player::Player(std::string s) { name = s; transform->RenderPriority = RenderPriorityType::PlayerAndObject ; }
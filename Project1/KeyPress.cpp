#include "SFML.h"
#include "WorldControl.h"
#include "Player.h"
#include<iostream>
View& view();
void KeyHold() {
    float speed=8.0;
    shared_ptr<Player> player = WorldControl::player().lock();
    if (Keyboard::isKeyPressed(Keyboard::Escape))
        WorldControl::window().close();
    if (Keyboard::isKeyPressed(Keyboard::A))
        player->transform->Move(Vector2f(-2*speed, 0));
    if (Keyboard::isKeyPressed(Keyboard::D))
        player->transform->Move(Vector2f(2*speed, 0));
    if (Keyboard::isKeyPressed(Keyboard::W))
        player->transform->Move(Vector2f(0, -2*speed));
    if (Keyboard::isKeyPressed(Keyboard::S))
        player->transform->Move(Vector2f(0, 2*speed));
}
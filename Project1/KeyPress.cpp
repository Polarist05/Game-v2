#include "SFML.h"
#include "WorldControl.h"
#include "Player.h"
#include<iostream>
View& view();
void KeyHold() {
    shared_ptr<Player> player = WorldControl::player().lock();
    if (Keyboard::isKeyPressed(Keyboard::Escape))
        WorldControl::window().close();
    if (Keyboard::isKeyPressed(Keyboard::A))
        player->transform.Move(Vector2f(-2, 0));
    if (Keyboard::isKeyPressed(Keyboard::D))
        player->transform.Move(Vector2f(2, 0));
    if (Keyboard::isKeyPressed(Keyboard::W))
        player->transform.Move(Vector2f(0, -2));
    if (Keyboard::isKeyPressed(Keyboard::S))
        player->transform.Move(Vector2f(0, 2));
    if (Keyboard::isKeyPressed(Keyboard::J))
        player->transform.SetScale(player->transform.scale+Vector2f(0.005,0.005));
}
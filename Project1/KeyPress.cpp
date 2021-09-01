#include "SFML.h"
#include "WorldControl.h"
#include "Player.h"
#include<iostream>
View& view();
void KeyHold() {
    Player player;
    if (Keyboard::isKeyPressed(Keyboard::Escape))
        WorldControl::window().close();
    if (Keyboard::isKeyPressed(Keyboard::A))
        player.Sprite().move(Vector2f(-10., 0.));
    if (Keyboard::isKeyPressed(Keyboard::D))
        player.Sprite().move(Vector2f(10., 0.));
    if (Keyboard::isKeyPressed(Keyboard::W))
        player.Sprite().move(Vector2f(0., -10.));
    if (Keyboard::isKeyPressed(Keyboard::S))
        player.Sprite().move(Vector2f(0., 10.));
    if (Keyboard::isKeyPressed(Keyboard::F))
        player.Sprite().setScale(2, 2);

}
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
        player->transform.renderBox.move(Vector2f(-10., 0.));
    if (Keyboard::isKeyPressed(Keyboard::D))
        player->transform.renderBox.move(Vector2f(10., 0.));
    if (Keyboard::isKeyPressed(Keyboard::W))
        player->transform.renderBox.move(Vector2f(0., -10.));
    if (Keyboard::isKeyPressed(Keyboard::S))
        player->transform.renderBox.move(Vector2f(0., 10.));
    if (Keyboard::isKeyPressed(Keyboard::I))
        player-> transform.SetAnchorType(AnchorType::TopLeft,BoxType::HitBox);
    if (Keyboard::isKeyPressed(Keyboard::O))
        player->transform.SetAnchorType(AnchorType::TopCentor, BoxType::HitBox);
    if (Keyboard::isKeyPressed(Keyboard::P))
        player->transform.SetAnchorType(AnchorType::TopRight, BoxType::HitBox);
    if (Keyboard::isKeyPressed(Keyboard::K))
        player->transform.SetAnchorType(AnchorType::MiddleLeft, BoxType::HitBox);
    if (Keyboard::isKeyPressed(Keyboard::L))
        player->transform.SetAnchorType(AnchorType::MiddleCentor, BoxType::HitBox);
    if (Keyboard::isKeyPressed(Keyboard::SemiColon))
        player->transform.SetAnchorType(AnchorType::MiddleRight, BoxType::HitBox);
    if (Keyboard::isKeyPressed(Keyboard::M))
        player->transform.SetAnchorType(AnchorType::DownLeft, BoxType::HitBox);
    if (Keyboard::isKeyPressed(Keyboard::Comma))
        player->transform.SetAnchorType(AnchorType::DownCentor, BoxType::HitBox);
    if (Keyboard::isKeyPressed(Keyboard::Period))
        player->transform.SetAnchorType(AnchorType::DownRight, BoxType::HitBox);
    if (Keyboard::isKeyPressed(Keyboard::J))
        player->transform.hitBox.setScale(player->transform.hitBox.getScale()+Vector2f(0.005,0.005));
}
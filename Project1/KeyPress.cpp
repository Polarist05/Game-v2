#include "SFML.h"
#include "WorldControl.h"
#include "Player.h"
#include<iostream>
#include "Knife.h"
View& view();
void KeyHold() {
    float speed=2.0;
    shared_ptr<Player> player = WorldControl::player().lock();
    if (!player->isAttacking&&!player->isHooking&&WControl::isGamePlaying) {
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            player->transform->Move(Vector2f(-2 * speed, 0));
            player->SetPlayerDirection(Direction::Left);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            player->transform->Move(Vector2f(2 * speed, 0));
            player->SetPlayerDirection(Direction::Right);
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            player->transform->Move(Vector2f(0, -2 * speed));
            player->SetPlayerDirection(Direction::Up);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            player->transform->Move(Vector2f(0, 2 * speed));
            player->SetPlayerDirection(Direction::Down);
        }
        if (Keyboard::isKeyPressed(Keyboard::R)) {
            player->MeleeAttack();
        }
        if (Keyboard::isKeyPressed(Keyboard::F)) {
            if (!WControl::player().lock()->isHoldHookButton) {
                WControl::player().lock()->isHoldHookButton = true;
                WControl::player().lock()->HoldingDirection = WControl::player().lock()->GetPlayerDirection();
                switch (WControl::player().lock()->HoldingDirection)
                {
                case Right:
                case Left:
                    WControl::player().lock()->hookGuideLine.setRotation(0);
                    break;
                case Up:
                case Down:
                    WControl::player().lock()->hookGuideLine.setRotation(90);
                    break;
                }
            }
            WControl::GetCurrentRoom().lock()->CheckNearestObjectHooking();
            if(WControl::player().lock()->hookGuideLine.getFillColor()!= Color::Red)
                WControl::player().lock()->hookGuideLine.setFillColor(Color::Red);
        }
        else if (WControl::player().lock()->isHoldHookButton) {
            if (WControl::player().lock()->canHook) {
                WControl::player().lock()->ActivateHooking();
            }
            WControl::player().lock()->isHoldHookButton = false;
            WControl::player().lock()->hookGuideLine.setFillColor(Color::Transparent);
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape) && WControl::UIStack().empty()) {
            WControl::UIStack().push(UIType::StartUI);
        }
        static bool holdThrowingButton;
        if (Keyboard::isKeyPressed(Keyboard::C)) {
            
            if (!holdThrowingButton&&WControl::player().lock()->HaveSoul(1)) {
                WControl::player().lock()->knifes.push(Instantiate<Knife>("knife"));
                holdThrowingButton = true;
                WControl::player().lock()->LostSoul(1);
            }
        }
        else
        {
            holdThrowingButton = false;
        }
    }
    static bool isLeftMouseHold;
    if (Mouse::isButtonPressed(Mouse::Button::Left)) {
        if (!isLeftMouseHold)
            isLeftMouseHold = true;
    }
    else if (isLeftMouseHold) {
        isLeftMouseHold = false;
        if (!WControl::clickableSpriteAtCursor().expired()) {
            WControl::clickableSpriteAtCursor().lock()->Activate();
        }
    }

}
#include "SFML.h"
#include "WorldControl.h"
#include "Player.h"
#include<iostream>
#include "Knife.h"
static float speed = 2.0;
static bool holdThrowingButton;
void KeyPress::CheckPlayerMovement() {
    static shared_ptr<Player> player = WControl::player().lock();
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
}
char KeyPress::CheckAlphaBetOrNumberKey() {
    for (char c = 'a'; c <= 'z'; c++) {
        if (Keyboard::isKeyPressed((Keyboard::Key)(c - 'a' + Keyboard::Key::A))) {
            return c;
        }
    }
    for (char c = '0'; c <= '9'; c++) {
        if (Keyboard::isKeyPressed((Keyboard::Key)(c - '0' + Keyboard::Key::Num0))) {
            return c;
        }
    }
    return 0;
}
void KeyPress::CheckPlayerAction() {
    if (Keyboard::isKeyPressed(Keyboard::R)) {
        WControl::player().lock()->MeleeAttack();
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
        if (WControl::player().lock()->hookGuideLine.getFillColor() != Color::Red)
            WControl::player().lock()->hookGuideLine.setFillColor(Color::Red);
    }
    else if (WControl::player().lock()->isHoldHookButton) {
        if (WControl::player().lock()->canHook) {
            WControl::player().lock()->ActivateHooking();
        }
        WControl::player().lock()->isHoldHookButton = false;
        WControl::player().lock()->hookGuideLine.setFillColor(Color::Transparent);
    }
    if (Keyboard::isKeyPressed(Keyboard::C)) {

        if (!holdThrowingButton && WControl::player().lock()->HaveSoul(1)) {
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
void KeyPress::CheckEscape() {
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        Mode::currentMode() = Mode::mainMenuMode();
        while (!WControl::UIStack().empty()) {
            WControl::UIStack().pop();
        }
        WControl::UIStack().push(UIType::StartPage);
    }
}
void KeyPress::CheckClickableSprite() {
    static bool isLeftMouseHold=false;
    if (Mouse::isButtonPressed(Mouse::Button::Left)) {
        if(!isLeftMouseHold)
            isLeftMouseHold = true;
    }
    else if(isLeftMouseHold){
        isLeftMouseHold = false;
        if (!WControl::clickableSpriteAtCursor().expired()) {
            WControl::clickableSpriteAtCursor().lock()->Activate();
        }
    }
}
void KeyPress::CheckEditArea() {
    if (Mouse::isButtonPressed(Mouse::Button::Left)) {
        Vector2i areaPosition = WControl::GetCurrentRoom().lock()->GetTransform()->GetPositionInTileAt(WControl::GetCursurPosition());
        if (WControl::clickableSpriteAtCursor().expired() && areaPosition.x < RSIZEX + 1 && areaPosition.y < RSIZEY + 1 && areaPosition.x>0 && areaPosition.y>0) {
            if (!Keyboard::isKeyPressed(Keyboard::LShift)) {
                WControl::GetChosedAreaPosition().clear();
            }
            WControl::GetChosedAreaPosition()[areaPosition.x].insert(areaPosition.y);
        }
    }
}
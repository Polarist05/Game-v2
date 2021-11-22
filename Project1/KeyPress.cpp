#include "SFML.h"
#include "WorldControl.h"
#include "Player.h"
#include<iostream>
#include "Knife.h"
static float speed = 2.0;
static bool holdThrowingButton;
void KeyPress::CheckPlayerMovement() {
    static shared_ptr<Player> player = WControl::player().lock();
    static bool isMoveLastFrame=false;
    Vector2f v;
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        v += Vector2f(-2 * speed, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        v += Vector2f(2 * speed, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        v += Vector2f(0, -2 * speed);
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        v += Vector2f(0, 2 * speed);
    }
    WControl::player().lock()->Walk(v);
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
    if (Keyboard::isKeyPressed(Keyboard::J)) {
        WControl::player().lock()->MeleeAttack();
    }
    if (Keyboard::isKeyPressed(Keyboard::L)) {
        if (WControl::player().lock()->playerState != e_Attacking && WControl::player().lock()->playerState != e_Hooking) 
        {
            if (WControl::player().lock()->playerState != e_Aiming) {
                WControl::sound()["Charge"].play();
                WControl::player().lock()->playerState = e_Aiming;
                Direction playerDirecction= WControl::player().lock()->GetPlayerDirection();
                WControl::player().lock()->HoldingDirection = playerDirecction;
                WControl::player().lock()->SetTexture(PlayerState::e_Aiming, playerDirecction);
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
    }
    else if (WControl::player().lock()->playerState==e_Aiming) {
        WControl::sound()["Charge"].stop();
        if (WControl::player().lock()->canHook) {
            WControl::player().lock()->ActivateHooking();
            WControl::player().lock()->playerState = e_Hooking;
        }
        else 
        {
            WControl::player().lock()->playerState = e_Stop;
            WControl::player().lock()->SetTexture(e_Stop,WControl::player().lock()->GetPlayerDirection());
        }
        WControl::player().lock()->hookGuideLine.setFillColor(Color::Transparent);
    }
    if (Keyboard::isKeyPressed(Keyboard::K)) {

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
        Mode::currentMode().lock()->SetUp();
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
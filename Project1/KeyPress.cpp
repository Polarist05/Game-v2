#include "SFML.h"
#include "WorldControl.h"
#include "Player.h"
#include<iostream>
#include "Knife.h"
View& view();
void KeyHold() {
    float speed=2.0;
    shared_ptr<Player> player = WorldControl::player().lock();
    if (!player->isAttacking&&!player->isHooking&& WControl::getGameMode() == GameMode::PlayMode) {
        
        if (Keyboard::isKeyPressed(Keyboard::R)) {
            player->MeleeAttack();
        }
        if (Keyboard::isKeyPressed(Keyboard::Y)) {
            cout << WControl::allRoomPrefabs().size();
            cout << endl;
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
            WControl::getGameMode() = GameMode::StartPageMode;
            WControl::UIStack().push(UIType::StartPage);
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
    static bool isLeftMouseHold;
    //printf("%d %d\n", WControl::GetCurrentRoom().lock()->GetTransform()->GetPositionInTileAt(WControl::GetCursurPosition()).x, WControl::GetCurrentRoom().lock()->GetTransform()->GetPositionInTileAt(WControl::GetCursurPosition()).y);
    if (Mouse::isButtonPressed(Mouse::Button::Left)) {
        if (!isLeftMouseHold)
            isLeftMouseHold = true;
        Vector2i areaPosition = WControl::GetCurrentRoom().lock()->GetTransform()->GetPositionInTileAt(WControl::GetCursurPosition());
        if (WControl::clickableSpriteAtCursor().expired()&&areaPosition.x < RSIZEX + 1 && areaPosition.y < RSIZEY + 1 && areaPosition.x>0 && areaPosition.y>0) {
            if (!Keyboard::isKeyPressed(Keyboard::LShift)) {
                WControl::GetChosedAreaPosition().clear();
            }
            WControl::GetChosedAreaPosition()[areaPosition.x].insert(areaPosition.y);
        }
        else {
            //WControl::GetChosedAreaPosition().clear();
        }
    }
    else if (isLeftMouseHold) {
        isLeftMouseHold = false;
        if (!WControl::clickableSpriteAtCursor().expired()) {
            WControl::clickableSpriteAtCursor().lock()->Activate();
        }
    }

}
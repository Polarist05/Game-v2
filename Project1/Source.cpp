#include "GameSprite.h"
#include "WorldControl.h"
#include <iostream>
#include <stdio.h>
#include "Player.h"
#include "Collision.h"
#include "Tile.h"
#include "Room.h"
using namespace sf;
using namespace std;
void ActivateStart();
void ActivateUpdate();
void KeyHold();
View _view(Vector2f(0,0),Vector2f(1920,1080));
View& view() { return _view; }
class a1 :public GameSprite {
public:
    a1(std::string s):GameSprite(s){}
};
void f1(),CheckAllSpriteName(weak_ptr<GameSprite> a,int b);
int main(){
    weak_ptr<Room> room= Instantiate<Room>("Room1");
    room.lock()->GetTransform()->SetParent(WorldControl::MainTile());
    room.lock()->f1();
    WorldControl::window().setFramerateLimit(60);
    WorldControl::window().setKeyRepeatEnabled(false);
    ActivateStart();
    while (WorldControl::window().isOpen())
    {   
        if (Keyboard::isKeyPressed(Keyboard::K)) {
            room.lock()->GetTransform()->SetPositionInTile(Vector2i(0, 0));
            printf("In");
        }
        WorldControl::window().clear(sf::Color::Red);
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (WorldControl::window().pollEvent(event))
        {
            // "close requested" event: we close the
            if (event.type == Event::Closed)
                WorldControl::window().close();
        }
        WorldControl::window().setView(view());
        f1();
        KeyHold();
        ActivateUpdate();
        WorldControl::window().display();
    }
    cout << endl<<"end program"<<endl;
}
void f1() {
    weak_ptr<a1> sam = Instantiate<a1>("sam1");

    sam.lock()->transform->renderBox.setFillColor(Color::Black);
    sam.lock()->transform->SetPosition(Vector2f(0, 0), BoxType::HitBox);
    sam.lock()->transform->SetPosition(Vector2f(0, 0), BoxType::RenderBox);
    sam.lock()->transform->SetPosition(400, 0);
    sam.lock()->transform->SetSize(Vector2f(200, 200), BoxType::RenderBox);
    MoveAllSprites(WorldControl::Hierarchy(), 0, Vector2f(0, 0), Vector2f(1, 1));
    if (Collision::isCollision(WorldControl::player().lock()->transform->renderBox, sam.lock()->transform->renderBox))
    {
        WorldControl::player().lock()->transform->renderBox.setFillColor(Color::Green);
    }
    else
    {
        WorldControl::player().lock()->transform->renderBox.setFillColor(Color::Blue);
    }
    DrawAllSprites(WorldControl::Hierarchy());
    //CheckAllSpriteName(WorldControl::Hierarchy(), 0);
    //printf("\n");
    //CheckAllSpriteName(WorldControl::NotrenderSprite(),0);
    //printf("-------------------------------\n");
}
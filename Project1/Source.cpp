#include "GameSprite.h"
#include "WorldControl.h"
#include <iostream>
#include <stdio.h>
#include "Player.h"
#include "Collision.h"
using namespace sf;
using namespace std;
void ActivateStart();
void ActivateUpdate();
void KeyHold();
View _view(Vector2f(0,0),Vector2f(1920,1080));
View& view() { return _view; }

class a1 :public GameSprite {
public:
    a1(std::string s) :GameSprite(s) {}
    //a1(a1& a):GameSprite(a.name, a.transform.position, a.transform.scale,a.transform.OffsetHitBox,a.transform.OffsetRenderBox) {}
    //a1(std::string s,Vector2f v,Vector2f v1,Vector2f v2,Vector2f v3) :GameSprite(s,v,v1,v2,v3) {}
    //a1(std::string s, Vector2f v, Vector2f v1) :GameSprite(s, v, v1) {}
   
};
class a2 :public GameSprite {
public:
    a2(std::string s) { name = s; }
};
void f1();
int main(){
    WorldControl::window().setFramerateLimit(60);
    WorldControl::window().setKeyRepeatEnabled(false);
    ActivateStart();
    while (WorldControl::window().isOpen())
    {
        
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
    vector<weak_ptr<a1>>sam(6,weak_ptr<a1>());
    sam[0] = Instantiate<a1>("sam1");
    sam[1] = Instantiate<a1>("sam2");
    sam[2] = Instantiate<a1>("sam3");
    sam[3] = Instantiate<a1>("sam4");
    sam[4] = Instantiate<a1>("sam5");
    sam[5] = Instantiate<a1>("sam6");
    sam[0].lock()->transform.renderBox.setFillColor(Color::Black);
    sam[1].lock()->transform.renderBox.setFillColor(Color::Red);
    sam[2].lock()->transform.renderBox.setFillColor(Color::Green);
    sam[3].lock()->transform.renderBox.setFillColor(Color::Blue);
    sam[4].lock()->transform.renderBox.setFillColor(Color::Magenta);
    sam[5].lock()->transform.renderBox.setFillColor(Color::Yellow);
    for (int i = 0; i < 6; i++) {
        sam[i].lock()->transform.hitBox.setPosition(Vector2f(0, 0));
        sam[i].lock()->transform.renderBox.setPosition(Vector2f(0, 0));
        sam[i].lock()->transform.hitBox.setFillColor(Color::Cyan);
        sam[i].lock()->transform.SetSize(Vector2f(2, 2), BoxType::HitBox);
        sam[i].lock()->transform.SetSize(Vector2f(1.9, 1.9), BoxType::RenderBox);
        sam[i].lock()->transform.SetPosition(Vector2f(0, 0), BoxType::HitBox);
        sam[i].lock()->transform.SetPosition(Vector2f(0, 0), BoxType::RenderBox);
        sam[i].lock()->transform.SetPosition(0, 0);
        sam[i].lock()->transform.scale = Vector2f(float(100/(i+1)) , float(100/(i+1)) ) ;
    }
    sam[0].lock()->transform.Move(Vector2f(400,0));
    sam[0].lock()->transform.hitBox.setFillColor(Color::Green);
    MoveAllSprites(WorldControl::Hierarchy(), 0, Vector2f(0, 0), Vector2f(1, 1));
    if (Collision::isCollision(WorldControl::player().lock()->transform.renderBox, sam[0].lock()->transform.renderBox)) 
    {
        printf("123456\n");
        WorldControl::player().lock()->transform.renderBox.setFillColor(Color::Green);
    }
    else
    {
        printf("-----------\n");
        WorldControl::player().lock()->transform.renderBox.setFillColor(Color::Blue);
    }
    DrawAllSprites(WorldControl::Hierarchy());
    //MoveAndDrawAllSprites(WorldControl::Hierarchy(),0,Vector2f(0,0),Vector2f(1,1));
    for (int i = 0; i < 6; i++) {
        Destroy(sam[i]);
    }
}
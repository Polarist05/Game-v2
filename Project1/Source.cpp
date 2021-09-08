#include "GameSprite.h"
#include "WorldControl.h"
#include <iostream>
#include <stdio.h>
#include "Player.h"
using namespace sf;
using namespace std;
void ActivateStart();
void ActivateUpdate();
void KeyHold();
View _view(Vector2f(0,0),Vector2f(1920,1080));
View& view() { return _view; }
void f1(weak_ptr<GameSprite> a, int b) {
    vector< weak_ptr<GameSprite> > v;
    for (int i = 0; i < b; i++) { printf("\t"); }
        cout << a.lock()->name << endl;
    for (int i = 0; i < a.lock()->transform.childs.size(); i++) {
        if (!a.lock()->transform.childs[i].expired()) {
            f1(a.lock()->transform.childs[i], b + 1);
            v.push_back(a.lock()->transform.childs[i]);
            a.lock()->transform.childs[i].lock()->transform.childIndex = v.size() -1;
        }
    }
    a.lock()->transform.childs = v;
}
class a1 :public GameSprite {
public:
    a1(std::string s) {name = s;}
};
class a2 :public GameSprite {
public:
    a2(std::string s) { name = s; }
};
int main(){
    weak_ptr<a1> sam1 = Instantiate<a1>("sam1");
    //sam1.lock()->transform.SetParent(WorldControl::player());
    weak_ptr<GameSprite> sam2 = Instantiate<GameSprite>("sam2");
    //sam2.lock()->transform.SetParent(sam1);
    weak_ptr<a2> sam3 = Instantiate<a2>("sam3");
    //sam3.lock()->transform.SetParent(sam2);
    weak_ptr<a2> sam4 = Instantiate<a2>("sam4");
    //sam4.lock()->transform.SetParent(sam2);
    weak_ptr<GameSprite> sam5 = Instantiate<GameSprite>("sam5");
    //sam5.lock()->transform.SetParent(sam3);
    WorldControl::window().setFramerateLimit(60);
    WorldControl::window().setKeyRepeatEnabled(false);
    ActivateStart();
    f1(WorldControl::Hierarchy(),0);
    Destroy<a1>(sam1);
    f1(WorldControl::Hierarchy(), 0);
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
        KeyHold();
        ActivateUpdate();
        WorldControl::window().display();
    }
    cout << endl<<"end program"<<endl;
}
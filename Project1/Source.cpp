#include "SFML.h"
#include "WorldControl.h"
#include <iostream>
#include <stdio.h>
#include "Player.h"
#include "GameSprite.h"
using namespace sf;
using namespace std;
void ActivateStart();
void ActivateUpdate();
void KeyHold();
View _view(Vector2f(0,0),Vector2f(1920,1080));
View& view() { return _view; }
class  a1 :public GameSprite {};
class  a2 :public Player {};
int main() {
    weak_ptr<GameSprite> p2 = Instantiate<GameSprite>();
    weak_ptr<a1> p3 = Instantiate<a1>();
    WorldControl::window().setFramerateLimit(60);
    WorldControl::window().setKeyRepeatEnabled(false);
    weak_ptr<Player> player =  Instantiate<Player>();
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
        printf("123");
        WorldControl::window().setView(view());
        KeyHold();
        ActivateUpdate();
        WorldControl::window().display();
    }
    cout << endl<<"end program"<<endl;
}
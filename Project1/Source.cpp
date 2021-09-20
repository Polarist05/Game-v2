#include "GameSprite.h"
#include "WorldControl.h"
#include <iostream>
#include <stdio.h>
#include "Player.h"
#include "Collision.h"
#include "Tile.h"
#include "Room.h"
#include "GameRenderer.h"
#include "Dungeon.h"
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
int main(){
    Dungeon();
    weak_ptr<Room> room= Instantiate<Room>("Room1");
    room.lock()->GetTransform()->SetParent(WorldControl::MainTile());
    room.lock()->f1();
    GameRenderer gameRenderer;
    gameRenderer.SetRoom(room);
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
        MoveAllSprites(WorldControl::Hierarchy(), 0, Vector2f(0, 0), Vector2f(1, 1));
        //DrawAllSprites(WorldControl::Hierarchy());
        gameRenderer.RenderAll();
        KeyHold();
        ActivateUpdate();
        WorldControl::window().display();
    }
    cout << endl<<"end program"<<endl;
    
}

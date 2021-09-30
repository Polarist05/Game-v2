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
    LoadAllRoomPrefab();
    SetUsedRoomPrefab();
    Dungeon dungeon;
    GameRenderer gameRenderer;
    gameRenderer.SetRenderRoom(dungeon.Rooms[2][2]);
    weak_ptr<Room> aa[4] = { dungeon.Rooms[1][2],dungeon.Rooms[3][2],dungeon.Rooms[2][1],dungeon.Rooms[2][3] };
    gameRenderer.SetSubRenderRoom(aa);
    WorldControl::window().setFramerateLimit(60);
    WorldControl::window().setKeyRepeatEnabled(false);
    ActivateStart();
    while (WorldControl::window().isOpen())
    {   
        if (Keyboard::isKeyPressed(Keyboard::K)) {
            gameRenderer.SetRenderRoom(dungeon.Rooms[2][1]);
        }
        if (Keyboard::isKeyPressed(Keyboard::SemiColon)) {
            gameRenderer.SetRenderRoom(dungeon.Rooms[2][3]);
        }
        if (Keyboard::isKeyPressed(Keyboard::O)) {
            gameRenderer.SetRenderRoom(dungeon.Rooms[1][2]);
        }
        if (Keyboard::isKeyPressed(Keyboard::Comma)) {
            gameRenderer.SetRenderRoom(dungeon.Rooms[3][2]);
        }
        if (Keyboard::isKeyPressed(Keyboard::L)) {
            gameRenderer.SetRenderRoom(dungeon.Rooms[2][2]);
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
        view().setCenter(WorldControl::player().lock()->transform->renderBox.getPosition());
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

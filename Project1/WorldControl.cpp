#include "WorldControl.h"
#include "GameRenderer.h"
#include "AllButton.h"
#include <fstream>
#include<map>
#include<vector>
#include <iostream>
#include <filesystem>
#include <random>
using namespace std;
Vector2i viewSize(1, 1);
float worldScale = (float)0.7;
float WorldControl::WorldScale() { return worldScale; };
RenderWindow _window(VideoMode((int)(1920. * WorldControl::WorldScale()), (int)(1080. * WorldControl::WorldScale())), "My window");
RenderWindow& WorldControl::window() { return _window; }

View _view(Vector2f(AREA_SIZEX* (RSIZEX + 2)* (2.5), AREA_SIZEY* (RSIZEY + 2) * 2.5) - Vector2f(AREA_SIZEX / 2., AREA_SIZEY / 2.), Vector2f(1920 * viewSize.x, 1080 * viewSize.y));
View& WControl::view() { return _view; }

map<type_index, vector<shared_ptr<GameBaseClass> > > AllEntities;
map<type_index, vector<shared_ptr<GameBaseClass> > >& GetAllEntities() { return AllEntities; }

map<std::string, pair<pair<bool, bool>, vector< RoomData > > > _allRoomPrefabs;
map<std::string, pair<pair<bool, bool>, vector< RoomData > > >& WorldControl::allRoomPrefabs() { return _allRoomPrefabs; }

map< RoomType, vector< RoomData > > _usedRoomPrefabs;
map< RoomType, vector< RoomData > >& WorldControl::usedRoomPrefabs() { return _usedRoomPrefabs; };

map<char, Texture> _ASCIIPrefab;
map<char, Texture>& WorldControl::ASCIIPrefab() { return _ASCIIPrefab; }

map<std::string, Texture> _objectsPrefab;
map<std::string, Texture>& WorldControl::objectsPrefab() { return _objectsPrefab; };

map<std::string, Texture> _otherPrefab;
map<std::string, Texture>& WorldControl::otherPrefab() { return _otherPrefab; };

weak_ptr<GameSprite> _notRenderSprite = Instantiate<GameSprite>("NotRenderSprite");
weak_ptr<GameSprite> WorldControl::NotrenderSprite() { return _notRenderSprite; }

weak_ptr<Tile> _notRenderTile = Instantiate<Tile>("NotRenderTile");
weak_ptr<Tile> WorldControl::NotrenderTile() { return _notRenderTile; }

weak_ptr<Tilemap> _notRenderTilemap = Instantiate<Tilemap>("NotRenderTilemap");
weak_ptr<Tilemap> WorldControl::NotrenderTilemap() { return _notRenderTilemap; }

weak_ptr<GameSprite> _hierarchy = Instantiate<GameSprite>("hierarchy");
weak_ptr<GameSprite> WorldControl::Hierarchy() { return _hierarchy; }

weak_ptr<GameSprite> _UIhierarchy = Instantiate<GameSprite>("UIHierarchy");
weak_ptr<GameSprite> WorldControl::UIHierarchy() { return _UIhierarchy; }

weak_ptr<Tile> _RenderTile = Instantiate<Tile>("MainTile");
weak_ptr<Tile> WorldControl::MainTile() { return _RenderTile; }

Dungeon* _MainDungeon;
void WorldControl::SetMainDungeon(Dungeon* MainDungeon) { _MainDungeon = MainDungeon; }
Dungeon& WorldControl::getMainDungeon() { return *_MainDungeon; }

UX _UX(KEY_AMOUNT, SOUL_AMOUNT);
UX& WControl::GetUX() { return _UX; }

weak_ptr<Player> _player = Instantiate<Player>("player");
weak_ptr<Player> WorldControl::player() { return _player; }
weak_ptr<ClickableSprite> _clickableSpriteAtCursor;
weak_ptr<ClickableSprite>& WControl::clickableSpriteAtCursor() { return _clickableSpriteAtCursor; };

bool _isGamePlaying = false;
bool& WorldControl::isGamePlaying() { return _isGamePlaying; };

std::stack<UIType> _UIStack;
std::stack<UIType>& WorldControl::UIStack() { return _UIStack; }

map<UIType, UI*> _AllUI;
map<UIType, UI*>& WorldControl::AllUI() { return _AllUI; }

weak_ptr<ClickableSprite> _HoldItem;
weak_ptr<ClickableSprite> WorldControl::HoldItem() { return _HoldItem; }

Vector2i _currentRoom;
weak_ptr<Room> WorldControl::GetCurrentRoom() { return getMainDungeon().Rooms[GetCurrentRoomPosition().y][GetCurrentRoomPosition().x]; }
Vector2i& WorldControl::GetCurrentRoomPosition() { return _currentRoom; }
void WorldControl::SetCurrentRoomPositon(const Vector2i& currentRoom) {
	_currentRoom = currentRoom;
	SetViewPosition(WControl::GetCurrentRoom().lock()->MiddlePositionOfRoom());
}

void WControl::SetViewPosition(Vector2f pos) {
	WControl::view().setCenter(WControl::GetCurrentRoom().lock()->MiddlePositionOfRoom());
	WControl::UIHierarchy().lock()->transform->SetPosition(WControl::GetCurrentRoom().lock()->MiddlePositionOfRoom());
}

Texture _playerPrefab;
Texture* WControl::playerPrefab() { return &_playerPrefab; }
void WControl::LoadData() {
	LoadOtherPrefab();
	LoadAllASCII();
	LoadPlayerPerfab();
	LoadAllObjectPrefab();
	LoadAllRoomPrefab();
	LoadAllUI();
}
void WControl::LoadOtherPrefab() {
	Texture texture;
	texture.loadFromFile("Sprites\\Knife.png", IntRect(0, 0, 280, 70));
	texture.setSmooth(true);
	otherPrefab()["Knife"] = texture;
}
void WorldControl::LoadAllASCII() {
	for (string c = "A"; c[0] <= 'Z'; c[0]++) {
		sf::Texture texture;
		if (texture.loadFromFile("Sprites\\ASCII\\" + c + ".png", IntRect(0, 0, 20, 45))) {
			texture.setSmooth(true);
			ASCIIPrefab()[c[0]] = texture;
		}
	}
	for (string c = "0"; c[0] <= '9'; c[0]++) {
		sf::Texture texture;
		if (texture.loadFromFile("Sprites\\ASCII\\" + c + ".png", IntRect(0, 0, 20, 45))) {
			texture.setSmooth(true);
			ASCIIPrefab()[c[0]] = texture;
		}
	}
	{
		sf::Texture texture;
		if (texture.loadFromFile("Sprites\\ASCII\\null.png", IntRect(0, 0, 20, 45))) {
			texture.setSmooth(true);
			ASCIIPrefab()[' '] = texture;
		}
	}
}
void WorldControl::LoadPlayerPerfab() {
	if (!_playerPrefab.loadFromFile("Sprites\\Player.png", IntRect(0, 0, 150, 250))) {
		cout << "can't load Player Sprite" << endl;
		return;
	}
	Vector2f scale(0.8, 0.8);
	_playerPrefab.setSmooth(true);
	WControl::player().lock()->transform->renderBox.setTexture(playerPrefab());
	SpriteOffsetData spriteOffset(Vector2i(26, 26), Vector2i(98, 193), Vector2f(80, 65), Vector2f(0, 65), Vector2f(0, 0), float(0.75));
	player().lock()->transform->SetAllSpriteOffset(spriteOffset);
	player().lock()->transform->SetSize(player().lock()->transform->pseudoRenderBox.getSize() - Vector2f(20, 0), PseudoRenderBox);
}
void WorldControl::LoadAllObjectPrefab() {
	std::ifstream t_objectsPrefab("Sprites\\ObjectsPrefab.txt");
	int objectsAmount = 0;
	t_objectsPrefab >> objectsAmount;
	if (objectsAmount == 0) {
		printf("can't load object prefab.txt");
		return;
	}
	for (int i = 0; i < objectsAmount; i++) {
		std::string name;
		t_objectsPrefab >> name;
		sf::Texture texture;
		if (!texture.loadFromFile("Sprites\\" + name + ".png", IntRect(0, 0, 190, 250))) {
			cout << "can't load " << name << " objects" << endl;
			continue;
		}
		else {
			texture.setSmooth(true);
			objectsPrefab()[name] = texture;
		}
	}
	t_objectsPrefab.close();
}
void WorldControl::LoadAllRoomPrefab() {
	WorldControl::allRoomPrefabs().clear();
	std::ifstream t_roomsPrefab("Rooms\\RoomPrefab.txt");
	int roomGroupAmount;
	t_roomsPrefab >> roomGroupAmount;
	for (int i = 0; i < roomGroupAmount; i++) {
		std::string setName;
		int setSize;
		t_roomsPrefab >> setName >> setSize;
		t_roomsPrefab >> WorldControl::allRoomPrefabs()[setName].first.second;
		WorldControl::allRoomPrefabs()[setName].first.first = true;
		for (int j = 0; j < setSize; j++) {
			std::ifstream t_room("Rooms\\" + setName + '\\' + to_string(j));
			WorldControl::allRoomPrefabs()[setName].second.push_back(RoomData());
			RoomData& roomData = WorldControl::allRoomPrefabs()[setName].second[WorldControl::allRoomPrefabs()[setName].second.size() - 1];
			//name and type
			{
				int roomType;
				t_room >> roomData.name >> roomType;
				roomData.roomType = (RoomType)roomType;
			}
			//floor
			for (int k = 0; k < RSIZEY; k++) {
				for (int l = 0; l < RSIZEX; l++) {
					int b;
					t_room >> b;
					if (b) {
						roomData.floor[k][l] = true;
					}
					else
						roomData.floor[k][l] = false;
				}
			}
			//object
			for (int k = 0; k < RSIZEY; k++) {
				for (int l = 0; l < RSIZEX; l++) {
					t_room >> roomData.objects[k][l];
				}
			}
			//track
			for (int k = 0; k < RSIZEY; k++) {
				for (int l = 0; l < RSIZEX; l++) {
					t_room >> roomData.track[k][l];
				}
			}
			t_room.close();
		}
	}
	t_roomsPrefab.close();
}
void WorldControl::LoadAllUI() {
	sf::Texture texture;
	{
		_AllUI[UIType::StartPage] = new UI;
		auto& thisUI = *_AllUI[UIType::StartPage];
		std::string path = "Sprites\\UI\\StartUI\\";
		if (texture.loadFromFile(path + "Play" + ".png", IntRect(0, 0, 250, 65))) {
			Texture* newTexture = new Texture(texture);
			SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), viewSize.x);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<PlayButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(UIHierarchy());
			wp.lock()->transform->SetPosition(Vector2f(0, -100));
			thisUI.clickableTextureSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "Score" + ".png", IntRect(0, 0, 250, 65))) {
			Texture* newTexture = new Texture(texture);
			SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), viewSize.x);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<ScoreButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(UIHierarchy());
			wp.lock()->transform->SetPosition(Vector2f(0, 0));
			thisUI.clickableTextureSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "Toolkit" + ".png", IntRect(0, 0, 250, 65))) {
			Texture* newTexture = new Texture(texture);
			SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), viewSize.x);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<ToolkitButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(UIHierarchy());
			wp.lock()->transform->SetPosition(Vector2f(0, 100));
			thisUI.clickableTextureSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "Setting" + ".png", IntRect(0, 0, 250, 65))) {
			Texture* newTexture = new Texture(texture);
			SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), viewSize.x);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<SettingButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(UIHierarchy());
			wp.lock()->transform->SetPosition(Vector2f(0, 200));
			thisUI.clickableTextureSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "Exit" + ".png", IntRect(0, 0, 250, 65))) {
			Texture* newTexture = new Texture(texture);
			SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), viewSize.x);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<ExitButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(UIHierarchy());
			wp.lock()->transform->SetPosition(Vector2f(0, 300));
			thisUI.clickableTextureSprites.push_back(wp);
		}
		{
			weak_ptr<GameSprite> wp = Instantiate<GameSprite>();
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(UIHierarchy());
			wp.lock()->transform->SetSize(Vector2f(1920, 1080), RenderBox);
			wp.lock()->transform->renderBox.setFillColor(Color::Black);
			thisUI.NormalSprites.push_back(wp);
		}
	}
	{
		_AllUI[UIType::ToolkitPage] = new ToolkitUI;
		ToolkitUI& thisUI = *((ToolkitUI*)_AllUI[UIType::ToolkitPage]);
		std::string path = "Sprites\\UI\\Toolkit\\";
		{
			weak_ptr<GameSprite> wp = Instantiate<GameSprite>();
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(UIHierarchy());
			wp.lock()->transform->SetSize(Vector2f(380, 1080), RenderBox);
			wp.lock()->transform->renderBox.setFillColor(Color::Black);
			wp.lock()->transform->SetPosition(Vector2f((1920 - wp.lock()->transform->renderBox.getSize().x) / 2., 0));
			thisUI.NormalSprites.push_back(wp);
			thisUI.taskbar = wp;
		}
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(295, 45), Vector2f(295, 45), Vector2f(0, 0), Vector2f(0, 0), viewSize.x);
		SpriteOffsetData spriteOffsetData1(Vector2i(0, 0), Vector2i(20, 45), Vector2f(20, 45), Vector2f(0, 0), Vector2f(0, 0), viewSize.x);
		if (texture.loadFromFile(path + "TaskBar" + ".png", IntRect(0, 0, 295, 45))) {
			Texture* newTexture = new Texture(texture);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<SetDropDownButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, -400));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.dropDown1 = wp;
		}
		if (texture.loadFromFile(path + "CreateNewSet" + ".png", IntRect(0, 0, 295, 45))) {
			Texture* newTexture = new Texture(texture);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<CreateNewSetButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, -300));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.taskbarSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "TaskBar" + ".png", IntRect(0, 0, 295, 45))) {
			Texture* newTexture = new Texture(texture);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<ClickableSprite>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, -200));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.dropDown2 = wp;
		}
		if (texture.loadFromFile(path + "CreateNewRoom" + ".png", IntRect(0, 0, 295, 45))) {
			Texture* newTexture = new Texture(texture);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<CreateNewRoomButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, -100));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.taskbarSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "DeleteSet" + ".png", IntRect(0, 0, 295, 45))) {
			Texture* newTexture = new Texture(texture);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<DeleteSetButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, 0));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.taskbarSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "DeleteRoom" + ".png", IntRect(0, 0, 295, 45))) {
			Texture* newTexture = new Texture(texture);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<DeleteRoomButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, 100));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.taskbarSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "Edit" + ".png", IntRect(0, 0, 295, 45))) {
			Texture* newTexture = new Texture(texture);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<EditButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, 200));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.taskbarSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "Save" + ".png", IntRect(0, 0, 295, 45))) {
			Texture* newTexture = new Texture(texture);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<SaveButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, 300));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.taskbarSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "TaskBar" + ".png", IntRect(0, 0, 295, 45))) {
			Texture* newTexture = new Texture(texture);
			texture.setSmooth(true);
			for (int i = 0; i < 10; i++) {
				weak_ptr<SetDropDownListButton> wp = Instantiate<SetDropDownListButton>();
				wp.lock()->index = i;
				wp.lock()->transform->renderBox.setTexture(newTexture);
				wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
				wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
				wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
				wp.lock()->transform->SetParent(thisUI.dropDown1);
				wp.lock()->transform->SetPosition(Vector2f(0, 45 * (i + 1)));
				thisUI.clickableTextureSprites.push_back(wp);
				thisUI.dropDownList1.push_back(wp);
				thisUI.textDropDown1.push_back(vector<weak_ptr<GameSprite>>());
				for (int j = 0; j < 10; j++) {
					weak_ptr<GameSprite> wp1 = Instantiate<GameSprite>();
					wp1.lock()->transform->renderBox.setFillColor(Color::Transparent);
					wp1.lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
					wp1.lock()->transform->SetAllSpriteOffset(spriteOffsetData1);
					wp1.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
					wp1.lock()->transform->SetParent(wp);
					wp1.lock()->transform->SetPosition(Vector2f(-wp.lock()->transform->renderBox.getSize().x / 2 + wp1.lock()->transform->renderBox.getSize().x * (j + 1.5), 0));
					thisUI.NormalSprites2.push_back(wp1);
					thisUI.textDropDown1[i].push_back(wp1);
				}
			}
		}
		int i = 0;
		for (auto& wp : WControl::allRoomPrefabs()) {
			int j = 0;
			std::string s = wp.first;
			thisUI.listName[i] = s;
			for (; j < s.size(); j++) {
				if (s[j] >= 'a' && s[j] <= 'z')
					s[j] = s[j] - 'a' + 'A';
				thisUI.textDropDown1[i][j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[s[j]]);
			}
			for (; j < 10; j++) {
				thisUI.textDropDown1[i][j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
			}
			i++;
		}
		for (; i < 10; i++) {
			for (int j=0; j < 10; j++) {
				thisUI.textDropDown1[i][j].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
			}
		}
	}

}

void WorldControl::SaveAllRoomPrefab() {
	std::ofstream save("Rooms\\RoomPrefab.txt");
	save << WorldControl::allRoomPrefabs().size() << endl;
	for (auto it = WorldControl::allRoomPrefabs().begin(); it != WorldControl::allRoomPrefabs().end(); it++) {
		save << it->first << " " << it->second.second.size() << " " << it->second.first.second << endl;
		std::filesystem::remove_all("Rooms\\" + it->first);
		std::filesystem::create_directory("Rooms\\" + it->first);
		for (int i = 0; i < it->second.second.size(); i++) {
			std::ofstream rooomSave("Rooms\\" + it->first + '\\' + to_string(i));
			rooomSave << it->second.second[i].name << " " << it->second.second[i].roomType << endl;
			for (int j = 0; j < RSIZEY; j++) {
				for (int k = 0; k < RSIZEX; k++) {
					rooomSave << it->second.second[i].floor[j][k] << " ";
				}
				rooomSave << endl;
			}
			rooomSave << endl;
			for (int j = 0; j < RSIZEY; j++) {
				for (int k = 0; k < RSIZEX; k++) {
					rooomSave << it->second.second[i].objects[j][k] << " ";
				}
				rooomSave << endl;
			}
			rooomSave << endl;
			for (int j = 0; j < RSIZEY; j++) {
				for (int k = 0; k < RSIZEX; k++) {
					rooomSave << it->second.second[i].track[j][k] << " ";
				}
				rooomSave << endl;
			}
		}
	}
	save.close();
}
void WorldControl::RefreshRoomPrefrab() {
	std::ofstream save("Rooms\\RoomPrefab.txt");
	save << WorldControl::allRoomPrefabs().size() << endl;
	for (auto& it : WorldControl::allRoomPrefabs()) {
		save << it.first << " " << it.second.second.size() << " " << it.second.first.second << endl;
	}
	save.close();
}

void WorldControl::SetUsedRoomPrefab() {
	WorldControl::usedRoomPrefabs().clear();
	for (map<std::string, pair<pair<bool, bool>, vector< RoomData> > >::iterator it = WorldControl::allRoomPrefabs().begin(); it != WorldControl::allRoomPrefabs().end(); it++) {
		if (it->second.first.first && !it->second.first.second) {
			for (int i = 0; i < it->second.second.size(); i++) {
				WorldControl::usedRoomPrefabs()[it->second.second[i].roomType].push_back(it->second.second[i]);
			}
		}
	}
	for (int i = 0; i < (RoomType::Type22_Verticle + 1); i++) {
		auto rng = std::default_random_engine{};
		std::shuffle(WorldControl::usedRoomPrefabs()[(RoomType)i].begin(), WorldControl::usedRoomPrefabs()[(RoomType)i].end(), rng);
	}
}

//for.h file
RenderWindow& Player::window() { return _window; }
RenderWindow& GameRenderer::window() { return _window; }
weak_ptr<GameSprite> GameRenderer::player() { return _player; }
weak_ptr<GameSprite> GameSprite::GameTransform::Hierachy() { return _hierarchy; }
weak_ptr<GameSprite>GameRenderer::Hierachy() { return _hierarchy; }
weak_ptr<Tile> Tilemap::TilemapTransform::NotrenderTile() { return _notRenderTile; }
weak_ptr<Tilemap> Area::AreaTransform::NotrenderTilemap() { return _notRenderTilemap; }
weak_ptr<WorldControl> WorldControlInstant = Instantiate<WorldControl>();

Vector2f Multiple(const Vector2f& a, const Vector2f& b) { return Vector2f(a.x * b.x, a.y * b.y); }
Vector2f Multiple(const Vector2f& a, const Vector2f& b, const Vector2f& c) { return Vector2f(a.x * b.x * c.x, a.y * b.y * c.y); }
Vector2f Flip(const Vector2f& a) { return Vector2f(a.y, a.x); }
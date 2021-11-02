#include "Load.h"
#include "WorldControl.h"
#include <fstream>
#include <filesystem>
#include "AllButton.h"

void Load::LoadData() {
	LoadAllOtherPrefab();
	LoadAllASCII();
	LoadPlayerPerfab();
	LoadAllObjectPrefab();
	LoadAllRoomPrefab();
	LoadAllUI();
}
void Load::LoadAllOtherPrefab() {
	LoadOtherPrefab("Knife", "Sprites", IntRect(0, 0, 280, 70));
	LoadOtherPrefab("Null", "Sprites", IntRect(0, 0, 190, 250));
	{
		std::string path = "Sprites\\UI\\Toolkit";
		LoadOtherPrefab("TaskBar", path, IntRect(0, 0, 295, 45));
		LoadOtherPrefab("CreateNewSet", path, IntRect(0, 0, 295, 45));
		LoadOtherPrefab("CreateNewRoom", path, IntRect(0, 0, 295, 45));
		LoadOtherPrefab("CreateNewSet", path, IntRect(0, 0, 295, 45));
		LoadOtherPrefab("DeleteSet", path, IntRect(0, 0, 295, 45));
		LoadOtherPrefab("DeleteRoom", path, IntRect(0, 0, 295, 45));
		LoadOtherPrefab("Edit", path, IntRect(0, 0, 295, 45));
		LoadOtherPrefab("Save", path, IntRect(0, 0, 295, 45));
		LoadOtherPrefab("CreateNewSet", path, IntRect(0, 0, 295, 45));
		LoadOtherPrefab("TaskBar", path, IntRect(0, 0, 295, 45));
		LoadOtherPrefab("Next", path, IntRect(0, 0, 295, 45));
		LoadOtherPrefab("Previous", path, IntRect(0, 0, 295, 45));
		LoadOtherPrefab("ItemIcon", path, IntRect(0, 0, 80, 80));
		LoadOtherPrefab("CliffIcon", path, IntRect(0, 0, 190, 250));
		LoadOtherPrefab("FloorIcon", path, IntRect(0, 0, 190, 250));
		LoadOtherPrefab("In", path, IntRect(0, 0, 190, 140));
		LoadOtherPrefab("Out", path, IntRect(0, 0, 190, 140));
		LoadOtherPrefab("Wall", path, IntRect(0, 0, 190, 140));
		

	}
}
void Load::LoadOtherPrefab(const string& name, const string& path, const IntRect& intRect) {
	Texture texture;
	texture.loadFromFile(path + "\\" + name + ".png", intRect);
	texture.setSmooth(true);
	WControl::otherPrefab()[name] = texture;
}
void Load::LoadAllASCII() {
	for (string c = "A"; c[0] <= 'Z'; c[0]++) {
		sf::Texture texture;
		if (texture.loadFromFile("Sprites\\ASCII\\" + c + ".png", IntRect(0, 0, 20, 45))) {
			texture.setSmooth(true);
			WControl::ASCIIPrefab()[c[0]] = texture;
		}
	}
	for (string c = "0"; c[0] <= '9'; c[0]++) {
		sf::Texture texture;
		if (texture.loadFromFile("Sprites\\ASCII\\" + c + ".png", IntRect(0, 0, 20, 45))) {
			texture.setSmooth(true);
			WControl::ASCIIPrefab()[c[0]] = texture;
		}
	}
	{
		sf::Texture texture;
		if (texture.loadFromFile("Sprites\\ASCII\\null.png", IntRect(0, 0, 20, 45))) {
			texture.setSmooth(true);
			WControl::ASCIIPrefab()[' '] = texture;
		}
	}
}
void Load::LoadPlayerPerfab() {
	if (!WControl::playerPrefab()->loadFromFile("Sprites\\Player.png", IntRect(0, 0, 150, 250))) {
		cout << "can't load Player Sprite" << endl;
		return;
	}
	Vector2f scale(0.8, 0.8);
	WControl::playerPrefab()->setSmooth(true);
	WControl::player().lock()->transform->renderBox.setTexture(WControl::playerPrefab());
	SpriteOffsetData spriteOffset(Vector2i(26, 26), Vector2i(98, 193), Vector2f(80, 65), Vector2f(0, 65), Vector2f(0, 0), float(0.75));
	WControl::player().lock()->transform->SetAllSpriteOffset(spriteOffset);
	WControl::player().lock()->transform->SetSize(WControl::player().lock()->transform->pseudoRenderBox.getSize() - Vector2f(20, 0), PseudoRenderBox);
}
void Load::LoadAllObjectPrefab() {
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
			WControl::objectsPrefab()[name] = texture;
		}
	}
	t_objectsPrefab.close();
}
void Load::LoadAllRoomPrefab() {
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

void Load::LoadAllUI() {
	LoadStartUI();
	LoadToolkitUI();
}
void Load::LoadStartUI() {
	sf::Texture texture;
	{
		WControl::AllUI()[UIType::StartPage] = new UI;
		auto& thisUI = WControl::AllUI()[UIType::StartPage];
		std::string path = "Sprites\\UI\\StartUI\\";
		if (texture.loadFromFile(path + "Play" + ".png", IntRect(0, 0, 250, 65))) {
			Texture* newTexture = new Texture(texture);
			SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), VIEW_SIZE);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<PlayButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Vector2f(0, -100));
			thisUI->clickableTextureSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "Score" + ".png", IntRect(0, 0, 250, 65))) {
			Texture* newTexture = new Texture(texture);
			SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), VIEW_SIZE);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<ScoreButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Vector2f(0, 0));
			thisUI->clickableTextureSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "Toolkit" + ".png", IntRect(0, 0, 250, 65))) {
			Texture* newTexture = new Texture(texture);
			SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0),VIEW_SIZE);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<ToolkitButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Vector2f(0, 100));
			thisUI->clickableTextureSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "Setting" + ".png", IntRect(0, 0, 250, 65))) {
			Texture* newTexture = new Texture(texture);
			SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), VIEW_SIZE);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<SettingButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Vector2f(0, 200));
			thisUI->clickableTextureSprites.push_back(wp);
		}
		if (texture.loadFromFile(path + "Exit" + ".png", IntRect(0, 0, 250, 65))) {
			Texture* newTexture = new Texture(texture);
			SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), VIEW_SIZE);
			texture.setSmooth(true);
			weak_ptr<ClickableSprite> wp = Instantiate<ExitButton>();
			wp.lock()->transform->renderBox.setTexture(newTexture);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Vector2f(0, 300));
			thisUI->clickableTextureSprites.push_back(wp);
		}
		{
			weak_ptr<GameSprite> wp = Instantiate<GameSprite>();
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetSize(Vector2f(1920, 1080), RenderBox);
			wp.lock()->transform->renderBox.setFillColor(Color::Black);
			thisUI->NormalSprites.push_back(wp);
		}
	}
}
void Load::LoadToolkitUI() {
	sf::Texture texture;
	{
		WControl::AllUI()[UIType::ToolkitPage] = new ToolkitUI;
		ToolkitUI& thisUI = *((ToolkitUI*)WControl::AllUI()[UIType::ToolkitPage]);

		{
			thisUI.taskbar = Instantiate<GameSprite>();
			weak_ptr<GameSprite> wp = thisUI.taskbar;
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetSize(Vector2f(380, 1080), RenderBox);
			wp.lock()->transform->renderBox.setFillColor(Color::Black);
			wp.lock()->transform->SetPosition(Vector2f((1920 - wp.lock()->transform->renderBox.getSize().x) / 2., 0));
			thisUI.NormalSprites.push_back(wp);
		}
		{
			thisUI.dropDown1 = Instantiate<SetDropDownButton>("SetDropDown");
			weak_ptr<ClickableSprite> wp = thisUI.dropDown1;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["TaskBar"]);
			wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, -400));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.dropDown1.lock()->InstantList();
		}
		{
			thisUI.newSetButton = Instantiate<CreateNewSetButton>();
			weak_ptr<ClickableSprite> wp = thisUI.newSetButton;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["CreateNewSet"]);
			wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, -300));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.taskbarSprites.push_back(wp);

		}
		{
			thisUI.dropDown2 = Instantiate<RoomDropDownButton>("RoomDropDown");
			weak_ptr<ClickableSprite> wp = thisUI.dropDown2;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["TaskBar"]);
			wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, -200));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.dropDown2.lock()->InstantList();
		}
		{
			thisUI.newRoomButton = Instantiate<CreateNewRoomButton>();
			weak_ptr<ClickableSprite> wp = thisUI.newRoomButton;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["CreateNewRoom"]);
			wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, -100));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.taskbarSprites.push_back(wp);
		}
		{
			thisUI.deleteSetButton = Instantiate<DeleteSetButton>();
			weak_ptr<ClickableSprite> wp = thisUI.deleteSetButton;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["DeleteSet"]);
			wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, 0));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.taskbarSprites.push_back(wp);
		}
		{
			thisUI.deleteRoomButton = Instantiate<DeleteRoomButton>();
			weak_ptr<ClickableSprite> wp = thisUI.deleteRoomButton;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["DeleteRoom"]);
			wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, 100));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.taskbarSprites.push_back(wp);
		}
		{
			thisUI.editButton = Instantiate<EditButton>();
			weak_ptr<ClickableSprite> wp = thisUI.editButton;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Edit"]);
			wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(thisUI.taskbar);
			wp.lock()->transform->SetPosition(Vector2f(0, 200));
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.taskbarSprites.push_back(wp);
		}
		{
			thisUI.saveButton = Instantiate<SaveButton>();
			weak_ptr<ClickableSprite> wp = thisUI.saveButton;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Save"]);
			wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
			wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Multiple(WControl::view().getSize(),Vector2f(0.5,0.5))+Vector2f(-200,-50) );
			thisUI.clickableTextureSprites.push_back(wp);
		}
		{
			Vector2f areaSize(AREA_SIZEX, AREA_SIZEY);
			SpriteOffsetData spriteOffsetData(Vector2i(), (Vector2i)Multiple(areaSize,Vector2f(2,1)), Multiple(areaSize, Vector2f(2, 1)), Vector2f(), Vector2f(), 1.0);
			thisUI.choosingEdges[Direction::Up] = Instantiate<ChoosingEdge>();
			weak_ptr<ChoosingEdge> wp = thisUI.choosingEdges[Direction::Up];
			wp.lock()->direction = Up;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Multiple(areaSize, Vector2f(0, -3.5)));
			thisUI.clickableTextureSprites.push_back(wp);
		}
		{
			Vector2f areaSize(AREA_SIZEX, AREA_SIZEY);
			SpriteOffsetData spriteOffsetData(Vector2i(), (Vector2i)Multiple(areaSize,Vector2f(2,1)) , Multiple(areaSize, Vector2f(2, 1)), Vector2f(), Vector2f(), 1.0);
			thisUI.choosingEdges[Direction::Down] = Instantiate<ChoosingEdge>();
			weak_ptr<ChoosingEdge> wp = thisUI.choosingEdges[Direction::Down];
			wp.lock()->direction = Down;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Multiple(areaSize, Vector2f(0, 3.5)));
			thisUI.clickableTextureSprites.push_back(wp);
		}
		{
			Vector2f areaSize(AREA_SIZEX, AREA_SIZEY);
			SpriteOffsetData spriteOffsetData(Vector2i(), (Vector2i)Multiple(areaSize, Vector2f(1, 2)), Multiple(areaSize, Vector2f(1, 2)), Vector2f(), Vector2f(), 1.0);
			thisUI.choosingEdges[Direction::Right] = Instantiate<ChoosingEdge>();
			weak_ptr<ChoosingEdge> wp = thisUI.choosingEdges[Direction::Right];
			wp.lock()->direction = Right;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Multiple(areaSize, Vector2f(4.5, 0)));
			thisUI.clickableTextureSprites.push_back(wp);
		}
		{
			Vector2f areaSize(AREA_SIZEX, AREA_SIZEY);
			SpriteOffsetData spriteOffsetData(Vector2i(), (Vector2i)Multiple(areaSize, Vector2f(1, 2)), Multiple(areaSize, Vector2f(1, 2)), Vector2f(), Vector2f(), 1.0);
			thisUI.choosingEdges[Direction::Left] = Instantiate<ChoosingEdge>();
			weak_ptr<ChoosingEdge> wp = thisUI.choosingEdges[Direction::Left];
			wp.lock()->direction = Left;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Multiple(areaSize, Vector2f(-4.5, 0)));
			thisUI.clickableTextureSprites.push_back(wp);
		}
		{
			SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(80, 80), Vector2f(80, 80), Vector2f(0, 0), Vector2f(0, 0), 1);
			weak_ptr<ItemIconButton> wp = Instantiate<ItemIconButton>();
			thisUI.itemIconButton = wp;
			wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["ItemIcon"]);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Multiple(WControl::view().getSize(),Vector2f(-0.5,0.5))+Vector2f(100,-60) );
			wp.lock()->Setup();
			thisUI.clickableTextureSprites.push_back(wp);
			thisUI.taskbarSprites.push_back(wp);
		}
	}
}

void Load::SaveAllRoomPrefab() {
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
void Load::RefreshRoomPrefrab() {
	std::ofstream save("Rooms\\RoomPrefab.txt");
	save << WorldControl::allRoomPrefabs().size() << endl;
	for (auto& it : WorldControl::allRoomPrefabs()) {
		save << it.first << " " << it.second.second.size() << " " << it.second.first.second << endl;
	}
	save.close();
}
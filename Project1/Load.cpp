#include "Load.h"
#include "WorldControl.h"
#include <fstream>
#include <filesystem>
#include "AllButton.h"
#include "StartUI.h"

void Load::LoadData() {
	LoadAllOtherPrefab();
	LoadAllASCII();
	LoadPlayerPerfab();
	LoadAllObjectPrefab();
	LoadAllRoomPrefab();
	LoadScoreboard();
	LoadAudio();
	LoadMusic();
}
void Load::LoadAllOtherPrefab() {
	LoadOtherPrefab("Knife", "Sprites", IntRect(0, 0, 280, 70));
	LoadOtherPrefab("player2", "Sprites", IntRect(0, 0, 1068, 1350));
	LoadOtherPrefab("Null", "Sprites", IntRect(0, 0, 190, 250));
	LoadOtherPrefab("CornerUL", "Sprites\\Wall\\Corner", IntRect(0, 0, 190 , 140));
	LoadOtherPrefab("CornerUR", "Sprites\\Wall\\Corner", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("CornerDL", "Sprites\\Wall\\Corner", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("CornerDR", "Sprites\\Wall\\Corner", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("CornerRUL", "Sprites\\Wall\\CornerR", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("CornerRUR", "Sprites\\Wall\\CornerR", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("CornerRDL", "Sprites\\Wall\\CornerR", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("CornerRDR", "Sprites\\Wall\\CornerR", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("SideU", "Sprites\\Wall\\Side", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("SideD", "Sprites\\Wall\\Side", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("SideL", "Sprites\\Wall\\Side", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("SideR", "Sprites\\Wall\\Side", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("Floor", "Sprites", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("StartFloor", "Sprites", IntRect(0, 0, 190, 140));
	LoadOtherPrefab("Logo", "Sprites", IntRect(0, 0, 915, 455));
	LoadOtherPrefab("Fireflies", "Sprites", IntRect(0, 0, 915, 455));
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
void Load::LoadObjectPrefab(const string& name, const string& path, const IntRect& intRect) {
	Texture texture;
	if (texture.loadFromFile(path + "\\" + name + ".png", intRect)) {
		texture.setSmooth(true);
		WControl::objectsPrefab()[name] = texture;
	}
}
void Load::LoadOtherPrefab(const string& name, const string& path, const IntRect& intRect) {
	Texture texture;
	if (texture.loadFromFile(path + "\\" + name + ".png", intRect))
	{
		texture.setSmooth(true);
		WControl::otherPrefab()[name] = texture;
	}
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
	WControl::player().lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["player2"]);
	SpriteOffsetData spriteOffset(Vector2i(0,0),Vector2i(PLAYERSIZE_X,PLAYERSIZE_Y), Vector2f(50, 20), Vector2f(0, 35), Vector2f(0, 0), float(1.2));
	WControl::player().lock()->transform->SetAllSpriteOffset(spriteOffset);
	WControl::player().lock()->transform->SetSize(Vector2f(100, 130), PseudoRenderBox);
	WControl::player().lock()->transform->SetSize(WControl::player().lock()->transform->pseudoRenderBox.getSize() - Vector2f(20, 0), PseudoRenderBox);
}
void Load::LoadAllObjectPrefab() {
	std::string path = "Sprites";
	IntRect objectRect(0, 0, 190, 250);
	LoadObjectPrefab("ChargeSoul", path, objectRect);
	LoadObjectPrefab("Bell", path, objectRect);
	LoadObjectPrefab("Hook", path, objectRect);
	for(int i=0;i<10;i++)
		LoadObjectPrefab("Portal"+to_string(i), path+"\\Portals", objectRect);
	LoadObjectPrefab("Strawberry", path, objectRect);
	LoadObjectPrefab("MovingPlatform", path, objectRect);
	LoadObjectPrefab("Switch", path, objectRect);
	LoadObjectPrefab("Switch2", path, objectRect);
	LoadObjectPrefab("NormalBlock", path, objectRect);
	LoadObjectPrefab("DeleteBlock", path, objectRect);
	LoadObjectPrefab("SignalBlock", path, objectRect);
	LoadObjectPrefab("MoveableBlock", path, objectRect);
	LoadObjectPrefab("Key", path, IntRect(0, 0, 250, 250));
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


void Load::SaveScoreboard() {
	std::ofstream save("Scoreboard.txt");
	for (auto& wp:WControl::scoreboard()) {
		save << wp.first<<" "<<wp.second<<endl;
	}
	save.close();
}
void Load::LoadScoreboard() {
	std::ifstream load("Scoreboard.txt");
	for (auto& wp : WControl::scoreboard()) {
		load >> wp.first>>wp.second;
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
void Load::LoadAudio() 
{
	std::string path = "Audio";
	LoadSingleSoundBuffer("FootStep",path,"wav",true);
	LoadSingleSoundBuffer("Charge", path, "wav", true);
	LoadSingleSoundBuffer("Hit", path, "wav", false);
	LoadSingleSoundBuffer("Push", path, "wav", false);
	LoadSingleSoundBuffer("KnifeStop", path, "wav", false);
	LoadSingleSoundBuffer("Throw", path, "wav", false);
	LoadSingleSoundBuffer("Wind", path, "wav", false);
	LoadSingleSoundBuffer("Beep", path, "wav", false);
	LoadSingleSoundBuffer("Attack", path, "wav", false);
	WControl::sound()["Attack"].setVolume(10);
	WControl::sound()["Wind"].setVolume(20);
}
void Load::LoadMusic()
{
	WControl::music().openFromFile("Audio\\Zelda.ogg");
	WControl::music().setVolume(10);
	WControl::music().setLoop(true);
}
void Load::LoadSingleSoundBuffer(const std::string& name, const std::string& path, const std::string& type, bool isLoop)
{
	WControl::soundBuffers()[name].loadFromFile(path+"\\"+name+"."+type);
	WControl::sound()[name].setBuffer(WControl::soundBuffers()[name]);
	WControl::sound()[name].setLoop(isLoop);
	WControl::sound()[name].setVolume(30);
}
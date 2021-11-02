#include "SaveButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"
#include <fstream>
#include <filesystem>
void SaveButton::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	bool isFlipX=0, isFlipY=0;
	RoomData& roomData=thisUI.newRoomData;
	{
		bool b=false;
		for (int i = 0; i<thisUI.newRoomData.objects.size();i++ ) {
			for (int j = 0;j< thisUI.newRoomData.objects[i].size();j++) {
				if (thisUI.newRoomData.objects[i][j]) {
					if (WControl::GetCurrentRoom().lock()->areas[i][j].lock()->transform->renderBox.getFillColor()==Color::Blue) {
						printf("You need to have floor at object place position\n");
						return;
					}
					if (thisUI.newRoomData.objects[i][j] == Strawberry * 10) {
						b = true;
					}
				}
			}
		}
		if (!b) {
			printf("You need atleast one Berry InRoom\n");
			return;
		}
	}
	if (thisUI.choosingEdges[Direction::Up].lock()->transform->renderBox.getTexture() == &WControl::otherPrefab()["In"] ) {
		if (thisUI.choosingEdges[Direction::Left].lock()->transform->renderBox.getTexture() == &WControl::otherPrefab()["In"]) {
			printf("You can't have In Edge two ways\n");
			return;
		}
		else {
			int sumX = thisUI.choosingEdges[Direction::Left].lock()->transform->renderBox.getTexture() != &WControl::otherPrefab()["Wall"]?1:0;
			sumX+= thisUI.choosingEdges[Direction::Right].lock()->transform->renderBox.getTexture() != &WControl::otherPrefab()["Wall"] ? 1 : 0;
			int sumY = 1;
			sumY += thisUI.choosingEdges[Direction::Down].lock()->transform->renderBox.getTexture() != &WControl::otherPrefab()["Wall"] ? 1 : 0;
			printf("Type %d %d\n", sumY, sumX);
			if (sumX == 1 && thisUI.choosingEdges[Direction::Right].lock()->transform->renderBox.getTexture() != &WControl::otherPrefab()["Wall"]) {
				printf("FlipX\n");
				isFlipX = true;
			}
			switch (sumX+sumY*3)
			{
			case 3:roomData.roomType = RoomType::Type10; break;
			case 4:roomData.roomType = RoomType::Type11_Verticle; break;
			case 5:roomData.roomType = RoomType::Type12_Verticle; break;
			case 6:roomData.roomType = RoomType::Type20; break;
			case 7:roomData.roomType = RoomType::Type21_Verticle; break;
			case 8:roomData.roomType = RoomType::Type22_Verticle; break;
			}
		}
	}
	else if (thisUI.choosingEdges[Direction::Left].lock()->transform->renderBox.getTexture() == &WControl::otherPrefab()["In"]) {
		int sumX = 1;
		sumX += thisUI.choosingEdges[Direction::Right].lock()->transform->renderBox.getTexture() != &WControl::otherPrefab()["Wall"] ? 1 : 0;
		int sumY = thisUI.choosingEdges[Direction::Up].lock()->transform->renderBox.getTexture() != &WControl::otherPrefab()["Wall"] ? 1 : 0;
		sumY += thisUI.choosingEdges[Direction::Down].lock()->transform->renderBox.getTexture() != &WControl::otherPrefab()["Wall"] ? 1 : 0;
		printf("Type %d %d\n",sumY,sumX);
		if (sumY == 1 && thisUI.choosingEdges[Direction::Down].lock()->transform->renderBox.getTexture() != &WControl::otherPrefab()["Wall"]) {
			printf("FlipY\n");
			isFlipY = true;
		}
		switch (sumX + sumY * 3)
		{
		case 1:roomData.roomType = RoomType::Type01;break;
		case 2:roomData.roomType = RoomType::Type02;break;
		case 4:roomData.roomType = RoomType::Type11_Horizon;break;
		case 5:roomData.roomType = RoomType::Type12_Horizon;break;
		case 7:roomData.roomType = RoomType::Type21_Horizon;break;
		case 8:roomData.roomType = RoomType::Type22_Horizon;break;
		}
	}
	else {
		printf("You need to have one In Edge someway\n");
		return;
	}
	roomData.name = "NewRoom";
	
	for (int i = 0; i < RSIZEY; i++) {
		for (int j = 0; j < RSIZEX; j++) {
			if (WControl::GetCurrentRoom().lock()->areas[i][j].lock()->transform->renderBox.getFillColor() == Color::Blue)
				roomData.floor[i][j] = true;
			if (!WControl::GetCurrentRoom().lock()->Space[i][j].expired()) {
				auto index= WControl::GetCurrentRoom().lock()->Space[i][j].lock()->transform->typeIndex;
				
			}
		}
	}
	if(1){
		ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
		for (auto& wp : thisUI.choosingEdges)
			wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.itemIconButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.itemIconButton.lock()->cliffButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.itemIconButton.lock()->floorButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
		for (auto& wp : thisUI.itemIconButton.lock()->objectDropDowns)
			wp.lock()->transform->renderBox.setFillColor(Color::Transparent);

		for (auto& wp : thisUI.taskbarSprites) {
			wp.lock()->transform->renderBox.setFillColor(Color::White);
		}
		thisUI.taskbar.lock()->transform->renderBox.setFillColor(Color::Black);
		thisUI.dropDown1.lock()->SetAllVisible(true);
		thisUI.dropDown2.lock()->SetAllVisible(true);
		thisUI.itemIconButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.saveButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
	}
	if (isFlipX) {
		for (auto& it : roomData.floor) 
			reverse(it.begin(), it.end());
		for (auto& it : roomData.objects)
			reverse(it.begin(), it.end());
		for (auto& it : roomData.track)
			reverse(it.begin(), it.end());
	}
	if (isFlipY) {
		reverse(roomData.floor.begin(), roomData.floor.end());
		reverse(roomData.objects.begin(), roomData.objects.end());
		reverse(roomData.track.begin(), roomData.track.end());
	}
	WControl::allRoomPrefabs()[thisUI.choosingSet].second[thisUI.choosingRoomIndex]=thisUI.newRoomData ;
	{
		std::ofstream rooomSave("Rooms\\" + thisUI.choosingSet + '\\' + to_string(thisUI.choosingRoomIndex));
		rooomSave << roomData.name << " " << roomData.roomType << endl;
		for (int j = 0; j < RSIZEY; j++) {
			for (int k = 0; k < RSIZEX; k++) {
				rooomSave << roomData.floor[j][k] << " ";
			}
			rooomSave << endl;
		}
		rooomSave << endl;
		for (int j = 0; j < RSIZEY; j++) {
			for (int k = 0; k < RSIZEX; k++) {
				rooomSave << roomData.objects[j][k] << " ";
			}
			rooomSave << endl;
		}
		rooomSave << endl;
		for (int j = 0; j < RSIZEY; j++) {
			for (int k = 0; k < RSIZEX; k++) {
				rooomSave << roomData.track[j][k] << " ";
			}
			rooomSave << endl;
		}
		rooomSave.close();
		thisUI.updateText();
		WControl::GetCurrentRoom().lock()->ResetRoom();
		WControl::GetCurrentRoom().lock()->SetRoomSeed(WControl::allRoomPrefabs()[thisUI.choosingSet].second[thisUI.choosingRoomIndex], false, false);
	}
}

#include "EditButton.h"
#include "ToolkitUI.h"
#include "WorldControl.h"
void EditButton::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	thisUI.newRoomData = WControl::allRoomPrefabs()[thisUI.choosingSet].second[thisUI.choosingRoomIndex];
	switch(thisUI.newRoomData.roomType) {
	case RoomType::Type00:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		break;
	case RoomType::Type01:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		break;
	case RoomType::Type02:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		break;
	case RoomType::Type10:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		break;
	case RoomType::Type11_Horizon:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		break;
	case RoomType::Type11_Verticle:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		break;
	case RoomType::Type12_Horizon:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		break;
	case RoomType::Type12_Verticle:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		break;
	case RoomType::Type20:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		break;
	case RoomType::Type21_Horizon:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		break;
	case RoomType::Type21_Verticle:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		break;
	case RoomType::Type22_Horizon:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		break;
	case RoomType::Type22_Verticle:
		thisUI.choosingEdges[Up].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["In"]);
		thisUI.choosingEdges[Down].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Left].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		thisUI.choosingEdges[Right].lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Out"]);
		break;
	}
	for (auto& wp : thisUI.choosingEdges)
		wp.lock()->transform->renderBox.setFillColor(Color::White);
	thisUI.itemIconButton.lock()->transform->renderBox.setFillColor(Color::White);
	for (auto& wp : thisUI.taskbarSprites) {
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
	}
	thisUI.taskbar.lock()->transform->renderBox.setFillColor(Color::Transparent);
	thisUI.dropDown1.lock()->SetAllVisible(false);
	thisUI.dropDown2.lock()->SetAllVisible(false);
	thisUI.itemIconButton.lock()->transform->renderBox.setFillColor(Color::White);
	thisUI.saveButton.lock()->transform->renderBox.setFillColor(Color::White);
}

#pragma once
#include "UI.h"
#include "SetDropDownButton.h"
#include "RoomDropDownButton.h"
#include "CreateNewRoomButton.h"
#include "CreateNewSetButton.h"
#include "DeleteRoomButton.h"
#include "DeleteSetButton.h"
#include "EditButton.h"
#include "SaveButton.h"
#include "NextRoomButton.h"
#include "PreviousRoomButton.h"
#include "ChoosingEdge.h"
class ToolkitUI:public UI
{
	static void setText(vector<weak_ptr<GameSprite>>& textSprites, const std::string& s);
public:
	bool isOpendropDown2 = false;
	weak_ptr<GameSprite> taskbar;
	vector<weak_ptr<ClickableSprite>> taskbarSprites;
	
	weak_ptr < SetDropDownButton> dropDown1;
	weak_ptr < RoomDropDownButton> dropDown2;
	weak_ptr < CreateNewRoomButton> newRoomButton;
	weak_ptr < CreateNewSetButton> newSetButton;
	weak_ptr < DeleteRoomButton> deleteRoomButton;
	weak_ptr < DeleteSetButton> deleteSetButton;
	weak_ptr < EditButton> editButton;
	weak_ptr < SaveButton> saveButton;
	weak_ptr < NextRoomButton> nextRoomButton;
	weak_ptr < PreviousRoomButton> previouseRoomButton;
	weak_ptr <ChoosingEdge> choosingEdges[4];
	
	void ChangeSet(std::string setName);
	void ChangeRoom(int index);
	void updateText();

	int choosingRoomIndex = 2;
	string choosingSet="startRoom";
};


#pragma once
#include "UI.h"
class ToolkitUI:public UI
{
public:
	weak_ptr<GameSprite> taskbar;
	vector<weak_ptr<ClickableSprite>> taskbarSprites;
	
	weak_ptr < ClickableSprite> dropDown1;
	vector<weak_ptr<ClickableSprite>> dropDownList1;
	vector<vector<weak_ptr<GameSprite> > > textDropDown1;
	
	weak_ptr < ClickableSprite> dropDown2;
	vector<weak_ptr<ClickableSprite>> dropDownList2;
	vector<vector<weak_ptr<GameSprite> > > textDropDown2;
	
	vector<string> listName= vector<string>(10,string() );

	int choosingRoomIndex = 2;
	string choosingSet="NewSet3";
};


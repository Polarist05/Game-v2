#pragma once
#include "ClickableSprite.h"
#include "RoomDropDownList.h"
class RoomDropDownButton:public ClickableSprite
{
public:
	bool isOpen = false;
	int dropDownPage=0;

	void InstantList();
	RoomDropDownButton();
	RoomDropDownButton(std::string s);
	vector<weak_ptr<RoomDropDownList>> dropDownList;
	vector<vector<weak_ptr<GameSprite> > > textDropDown;
	vector<weak_ptr<GameSprite> > choosedText;
	void GotoNextPage();
	void GotoPreviousPage();
	void Open();
	void Close();
	void UpdateText();
	void Activate() override;
	void SetAllVisible(const bool b);
};


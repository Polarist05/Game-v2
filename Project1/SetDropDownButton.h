#pragma once
#include "ClickableSprite.h"
#include "SetDropDownListButton.h"
class SetDropDownButton : public ClickableSprite
{
public:
	void InstantList();
	bool isOpen = false;
	SetDropDownButton();
	SetDropDownButton(string s);
	vector<weak_ptr<SetDropDownListButton>> dropDownList;
	vector<vector<weak_ptr<GameSprite> > > textDropDown;
	vector<weak_ptr<GameSprite> > choosedText;
	void Open();
	void Close();
	void UpdateText();
	void Activate() override;
};


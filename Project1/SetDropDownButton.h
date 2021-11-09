#pragma once
#include "ClickableSprite.h"
#include "SetDropDownListButton.h"
#include "TextUI.h"
class SetDropDownButton : public ClickableSprite
{
public:
	void InstantList();
	bool isOpen = false;
	SetDropDownButton();
	SetDropDownButton(string s);
	vector<weak_ptr<SetDropDownListButton>> dropDownList;
	vector< TextUI > textDropDown;
	TextUI choosedText;
	void Open();
	void Close();
	void UpdateText();
	void Activate() override;
	void SetAllVisible(const bool& b);
};


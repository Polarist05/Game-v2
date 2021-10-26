#include "SetDropDownListButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"
#include <iostream>
void SetDropDownListButton::Activate()
{
	ToolkitUI& thisUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	if (thisUI.listName[index] != "") {
		cout << thisUI.listName[index] << endl;
		thisUI.choosingSet = thisUI.listName[index];
	}
	for (auto& wp : thisUI.dropDownList1) {
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
	}
	for (auto& wp : thisUI.textDropDown1) {
		for (auto& wp1 : wp) {
			wp1.lock()->transform->renderBox.setFillColor(Color::Transparent);
		}
	}
}
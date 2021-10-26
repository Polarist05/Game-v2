#include "SetDropDownButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"
void SetDropDownButton::Activate()
{
	ToolkitUI& toolkitUI = *(ToolkitUI*)(WControl::AllUI()[UIType::ToolkitPage]);
	for (auto& wp : toolkitUI.dropDownList1) {
		wp.lock()->transform->renderBox.setFillColor(Color::White);
	}
	for (auto& wp : toolkitUI.textDropDown1) {
		for (auto wp1 : wp) {
			wp1.lock()->transform->renderBox.setFillColor(Color::White);
		}
	}
}

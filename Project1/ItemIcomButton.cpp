#include "ItemIcomButton.h"
#include "WorldControl.h"
#include "ToolkitUI.h"
void ItemIconButton::Activate()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	if (objectDropDowns.begin()->lock()->transform->renderBox.getFillColor()==Color::Transparent) {
		for(auto& wp:objectDropDowns)
			wp.lock()->transform->renderBox.setFillColor(Color::White);
		floorButton.lock()->transform->renderBox.setFillColor(Color::White);
		cliffButton.lock()->transform->renderBox.setFillColor(Color::White);
		for (auto& wp : thisUI.choosingEdges)
			wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
	}
	else {
		for (auto& wp : objectDropDowns)
			wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		floorButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
		cliffButton.lock()->transform->renderBox.setFillColor(Color::Transparent);
		for (auto& wp : thisUI.choosingEdges)
			wp.lock()->transform->renderBox.setFillColor(Color::White);
	}
}

void ItemIconButton::Start()
{
	
}

void ItemIconButton::Setup()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	int i = 1;
	const std::array<std::string, 10> s = { "ChargeSoul","Bell","Hook","Portal","Strawberry","Switch","NormalBlock","DeleteBlock","SignalBlock","MoveableBlock" };
	for (auto& name : s) {
		objectDropDowns.push_back(Instantiate<ObjectDropDown>());
		objectDropDowns.rbegin()->lock()->SetType((ObjectType)(i));
		objectDropDowns.rbegin()->lock()->transform->renderBox.setTexture(&WControl::objectsPrefab()[name]);
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(190, 250), Vector2f(190, 250), Vector2f(0, 0), Vector2f(0, 0), 0.3);
		objectDropDowns.rbegin()->lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		objectDropDowns.rbegin()->lock()->transform->SetParent(transform->wp);
		objectDropDowns.rbegin()->lock()->transform->SetPosition(Vector2f(i * 80, 0));
		objectDropDowns.rbegin()->lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.clickableSprites.push_back(*objectDropDowns.rbegin());
		i++;
	}
	objectDropDowns[3].lock()->transform->renderBox.setTexture(&WControl::objectsPrefab()["Portal0"]);
	{
		objectDropDowns.push_back(Instantiate<ObjectDropDown>());
		objectDropDowns.rbegin()->lock()->SetType(ObjectType::Null);
		objectDropDowns.rbegin()->lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Null"]);
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(190, 250), Vector2f(190, 250), Vector2f(0, 0), Vector2f(0, 0), 0.3);
		objectDropDowns.rbegin()->lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		objectDropDowns.rbegin()->lock()->transform->SetParent(transform->wp);
		objectDropDowns.rbegin()->lock()->transform->SetPosition(Vector2f(i * 80, 0));
		objectDropDowns.rbegin()->lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.clickableSprites.push_back(*objectDropDowns.rbegin());
	}
	{
		thisUI.itemIconButton.lock()->cliffButton = Instantiate<CliffButton>("CliffButton");
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(190, 250), Vector2f(190, 250), Vector2f(0, 0), Vector2f(0, 0), 0.3);
		weak_ptr<CliffButton> wp = thisUI.itemIconButton.lock()->cliffButton;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["CliffIcon"]);
		wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(thisUI.itemIconButton);
		wp.lock()->transform->SetPosition(Vector2f(0, -80));
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.clickableSprites.push_back(wp);
	}
	{
		thisUI.itemIconButton.lock()->floorButton = Instantiate<FloorButton>("FloorButton");
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(190, 250), Vector2f(190, 250), Vector2f(0, 0), Vector2f(0, 0), 0.3);
		weak_ptr<FloorButton> wp = thisUI.itemIconButton.lock()->floorButton;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["FloorIcon"]);
		wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(thisUI.itemIconButton);
		wp.lock()->transform->SetPosition(Vector2f(0, -160));
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		thisUI.clickableSprites.push_back(wp);
	}
}

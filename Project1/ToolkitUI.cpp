#include "ToolkitUI.h"
#include "WorldControl.h"

ToolkitUI::ToolkitUI()
{
	sf::Texture texture;
	{
		taskbar = Instantiate<GameSprite>();
		weak_ptr<GameSprite> wp = taskbar;
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetSize(Vector2f(380, 1080), RenderBox);
		wp.lock()->transform->renderBox.setFillColor(Color::Black);
		wp.lock()->transform->SetPosition(Vector2f((1920 - wp.lock()->transform->renderBox.getSize().x) / 2., 0));
		NormalSprites.push_back(wp);
	}
	{
		dropDown1 = Instantiate<SetDropDownButton>("SetDropDown");
		weak_ptr<ClickableSprite> wp = dropDown1;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["TaskBar"]);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(taskbar);
		wp.lock()->transform->SetPosition(Vector2f(0, -400));
		clickableSprites.push_back(wp);
		dropDown1.lock()->InstantList();
	}
	{
		newSetButton = Instantiate<CreateNewSetButton>();
		weak_ptr<ClickableSprite> wp = newSetButton;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["CreateNewSet"]);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(taskbar);
		wp.lock()->transform->SetPosition(Vector2f(0, -300));
		clickableSprites.push_back(wp);
		taskbarSprites.push_back(wp);

	}
	{
		dropDown2 = Instantiate<RoomDropDownButton>("RoomDropDown");
		weak_ptr<ClickableSprite> wp = dropDown2;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["TaskBar"]);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(taskbar);
		wp.lock()->transform->SetPosition(Vector2f(0, -200));
		clickableSprites.push_back(wp);
		dropDown2.lock()->InstantList();
	}
	{
		newRoomButton = Instantiate<CreateNewRoomButton>();
		weak_ptr<ClickableSprite> wp = newRoomButton;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["CreateNewRoom"]);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(taskbar);
		wp.lock()->transform->SetPosition(Vector2f(0, -100));
		clickableSprites.push_back(wp);
		taskbarSprites.push_back(wp);
	}
	{
		deleteSetButton = Instantiate<DeleteSetButton>();
		weak_ptr<ClickableSprite> wp = deleteSetButton;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["DeleteSet"]);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(taskbar);
		wp.lock()->transform->SetPosition(Vector2f(0, 0));
		clickableSprites.push_back(wp);
		taskbarSprites.push_back(wp);
	}
	{
		deleteRoomButton = Instantiate<DeleteRoomButton>();
		weak_ptr<ClickableSprite> wp = deleteRoomButton;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["DeleteRoom"]);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(taskbar);
		wp.lock()->transform->SetPosition(Vector2f(0, 100));
		clickableSprites.push_back(wp);
		taskbarSprites.push_back(wp);
	}
	{
		editButton = Instantiate<EditButton>();
		weak_ptr<ClickableSprite> wp = editButton;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Edit"]);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(taskbar);
		wp.lock()->transform->SetPosition(Vector2f(0, 200));
		clickableSprites.push_back(wp);
		taskbarSprites.push_back(wp);
	}
	{
		saveButton = Instantiate<SaveButton>();
		weak_ptr<ClickableSprite> wp = saveButton;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Save"]);
		wp.lock()->transform->SetAllSpriteOffset(WControl::NormalButtonOffsetData());
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetPosition(Multiple(WControl::view().getSize(), Vector2f(0.5, 0.5)) + Vector2f(-200, -50));
		clickableSprites.push_back(wp);
	}
	{
		Vector2f areaSize(AREA_SIZEX, AREA_SIZEY);
		SpriteOffsetData spriteOffsetData(Vector2i(), (Vector2i)Multiple(areaSize, Vector2f(2, 1)), Multiple(areaSize, Vector2f(2, 1)), Vector2f(), Vector2f(), 1.0);
		choosingEdges[Direction::Up] = Instantiate<ChoosingEdge>();
		weak_ptr<ChoosingEdge> wp =choosingEdges[Direction::Up];
		wp.lock()->direction = Up;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetPosition(Multiple(areaSize, Vector2f(0, -3.5)));
		clickableSprites.push_back(wp);
	}
	{
		Vector2f areaSize(AREA_SIZEX, AREA_SIZEY);
		SpriteOffsetData spriteOffsetData(Vector2i(), (Vector2i)Multiple(areaSize, Vector2f(2, 1)), Multiple(areaSize, Vector2f(2, 1)), Vector2f(), Vector2f(), 1.0);
		choosingEdges[Direction::Down] = Instantiate<ChoosingEdge>();
		weak_ptr<ChoosingEdge> wp = choosingEdges[Direction::Down];
		wp.lock()->direction = Down;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetPosition(Multiple(areaSize, Vector2f(0, 3.5)));
		clickableSprites.push_back(wp);
	}
	{
		Vector2f areaSize(AREA_SIZEX, AREA_SIZEY);
		SpriteOffsetData spriteOffsetData(Vector2i(), (Vector2i)Multiple(areaSize, Vector2f(1, 2)), Multiple(areaSize, Vector2f(1, 2)), Vector2f(), Vector2f(), 1.0);
		choosingEdges[Direction::Right] = Instantiate<ChoosingEdge>();
		weak_ptr<ChoosingEdge> wp = choosingEdges[Direction::Right];
		wp.lock()->direction = Right;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetPosition(Multiple(areaSize, Vector2f(4.5, 0)));
		clickableSprites.push_back(wp);
	}
	{
		Vector2f areaSize(AREA_SIZEX, AREA_SIZEY);
		SpriteOffsetData spriteOffsetData(Vector2i(), (Vector2i)Multiple(areaSize, Vector2f(1, 2)), Multiple(areaSize, Vector2f(1, 2)), Vector2f(), Vector2f(), 1.0);
		choosingEdges[Direction::Left] = Instantiate<ChoosingEdge>();
		weak_ptr<ChoosingEdge> wp = choosingEdges[Direction::Left];
		wp.lock()->direction = Left;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Wall"]);
		wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetPosition(Multiple(areaSize, Vector2f(-4.5, 0)));
		clickableSprites.push_back(wp);
	}
	{
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(80, 80), Vector2f(80, 80), Vector2f(0, 0), Vector2f(0, 0), 1);
		weak_ptr<ItemIconButton> wp = Instantiate<ItemIconButton>();
		itemIconButton = wp;
		wp.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["ItemIcon"]);
		wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		wp.lock()->transform->renderBox.setFillColor(Color::Transparent);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetPosition(Multiple(WControl::view().getSize(), Vector2f(-0.5, 0.5)) + Vector2f(100, -60));
		wp.lock()->Setup();
		clickableSprites.push_back(wp);
		taskbarSprites.push_back(wp);
	}
}

void ToolkitUI::ChangeSet(std::string setName)
{
	if (setName != "") {
		choosingSet = setName;
		dropDown2.lock()->dropDownPage = 0;
		ChangeRoom(0);
	}
}

void ToolkitUI::ChangeRoom(int index)
{
	if (index < WControl::allRoomPrefabs()[choosingSet].second.size()) {
		choosingRoomIndex = index;
		WControl::GetCurrentRoom().lock()->ResetRoom();
		WControl::GetCurrentRoom().lock()->SetRoomSeed(WControl::allRoomPrefabs()[choosingSet].second[choosingRoomIndex], false, false);
	}
	else if (!WControl::allRoomPrefabs()[choosingSet].second.size()) {
		choosingRoomIndex = 0;
		WControl::GetCurrentRoom().lock()->ResetRoom();
		WControl::GetCurrentRoom().lock()->SetRoomSeed(RoomData(), false, false);
		updateText();
	}
	updateText();
}

void ToolkitUI::updateText()
{
	dropDown1.lock()->UpdateText();
	dropDown2.lock()->UpdateText();
}

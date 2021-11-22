#include "choosedGroupList.h"
#include "WorldControl.h"
choosedGroupList::choosedGroupList()
{
	background = Instantiate<GameSprite>("background");
	background.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
	background.lock()->transform->SetParent(WControl::UIHierarchy());
	background.lock()->transform->SetSize(Multiple((Vector2f)WControl::TextOffsetData().renderPixelSize,Vector2f(10.4,1.4)) , RenderBox);
	background.lock()->transform->renderBox.setFillColor(Color::Black);
	ALLUI::toolkitUI().NormalSprites.push_back(background);

	indexText.SetText("0123456789");
	indexText.SetParent(background);
	for(auto& wp:indexText.getSprites())
		ALLUI::toolkitUI().NormalSprites2.push_back(wp);


	clickSprites.SetParent(background);
	for (auto& wp : clickSprites.getSprites())
		ALLUI::toolkitUI().clickableSprites.push_back(wp);

	
	SetVisible(false);
}

void choosedGroupList::SetPosition(const Vector2f& v)
{
	background.lock()->transform->SetPosition(v);
}

void choosedGroupList::SetParent(const weak_ptr<GameSprite>& wp)
{
	background.lock()->transform->SetParent(wp);
}

void choosedGroupList::SetVisible(const bool& b)
{
	if (b)
	{
		background.lock()->transform->renderBox.setFillColor(Color::Black);
		indexText.SetColor(Color::White);
		clickSprites.SetColor(Color::White);
	}
	else 
	{
		background.lock()->transform->renderBox.setFillColor(Color::Transparent);
		indexText.SetColor(Color::Transparent);
		clickSprites.SetColor(Color::Transparent);
	}
}

void choosedGroupList::Release()
{
	auto wp= background.lock()->transform->wp;
	auto index =background.lock()->transform->typeIndex;
	Destroy(wp,index);
	indexText.Release();
	clickSprites.Release();
}

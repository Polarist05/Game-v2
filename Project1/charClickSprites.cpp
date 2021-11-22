#include "charClickSprites.h"
#include "WorldControl.h"

charClickSprites::charClickSprites()
{
	for (int i = 0; i < 10; i++) {
		spritelist.push_back(Instantiate<CharClickSprite>());
		spritelist.rbegin()->lock()->Setup(i);
		spritelist.rbegin()->lock()->transform->SetAllSpriteOffset(WControl::TextOffsetData());
		spritelist.rbegin()->lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		SetPosition(Vector2f(0, 0));
	}
}

Vector2f charClickSprites::GetPosition()
{
	return position;
}

void charClickSprites::SetTexture(Texture* texture)
{
	for (auto& wp : spritelist) {
		wp.lock()->transform->renderBox.setTexture(texture);
	}
}

void charClickSprites::SetPosition(const Vector2f& v)
{
	position = v;
	for (int i = 0; i < spritelist.size(); i++) 
	{
		spritelist[i].lock()->transform->SetPosition(v + Vector2f(spritelist[i].lock()->transform->renderBox.getSize().x * (i - 4.5), 0));
	}
}

void charClickSprites::SetParent(const weak_ptr<GameSprite>& wp)
{
	for (auto& charact : spritelist) {
		charact.lock()->transform->SetParent(wp);
	}
}

void charClickSprites::SetColor(const Color& color)
{
	for(auto& wp:spritelist)
	{
		wp.lock()->transform->renderBox.setFillColor(color);
	}
}

vector<weak_ptr<CharClickSprite> >& charClickSprites::getSprites()
{
	return spritelist;
}

void charClickSprites::Release()
{
	for (auto& wp : spritelist)
		Destroy(wp.lock()->transform->wp, wp.lock()->transform->typeIndex);
	spritelist.clear();
}


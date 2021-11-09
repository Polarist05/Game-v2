
#include "TextUI.h"
#include "WorldControl.h"
TextUI::TextUI()
{
	for (int i = 0; i < 10; i++) {
		charlist.push_back(Instantiate<GameSprite>());
		charlist.rbegin()->lock()->transform->SetAllSpriteOffset(WControl::TextOffsetData());
		charlist.rbegin()->lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		SetPosition(Vector2f(0, 0));
	}
}

Vector2f TextUI::GetPosition()
{
	return position;
}

void TextUI::SetText(const std::string& s)
{	

	for (int i = 0; i < 10; i++) {
		if (i < s.size()) {
			char c = (s[i] >= 'a' && s[i] <= 'z')?s[i]-'a'+'A' :s[i] ;
			charlist[i].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[c]);
		}
		else {
			charlist[i].lock()->transform->renderBox.setTexture(&WControl::ASCIIPrefab()[' ']);
		}
	}
}

void TextUI::SetPosition(const Vector2f& v)
{
	position = v;
	for (int i = 0; i < charlist.size(); i++) {
		charlist[i].lock()->transform->SetPosition(v+Vector2f(charlist[i].lock()->transform->renderBox.getSize().x * (i - 4.5),0));
	}
}

void TextUI::SetParent(const weak_ptr<GameSprite>& wp)
{
	for (auto& charact : charlist) {
		charact.lock()->transform->SetParent(wp);
	}
}

void TextUI::SetColor(const Color& b)
{
	for (auto wp : charlist) {
		if(!wp.expired())
			wp.lock()->transform->renderBox.setFillColor(b);
	}
}

vector<weak_ptr<GameSprite> >& TextUI::getSprites()
{
	return charlist;
}

void TextUI::Release()
{
	for (auto& wp : charlist)
		Destroy(wp.lock()->transform->wp, wp.lock()->transform->typeIndex);
	charlist.clear();
}


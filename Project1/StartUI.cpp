#include "StartUI.h"
#include "WorldControl.h"
StartUI::StartUI()
{
	Texture texture;
	std::string path = "Sprites\\UI\\StartUI\\";
	{
		logoSprite = Instantiate<GameSprite>("Logo");
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(915, 445), Vector2f(0,0), Vector2f(0, 0), Vector2f(0, 0), 0.9*VIEW_SIZE);
		logoSprite.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["Logo"]);
		logoSprite.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		logoSprite.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		logoSprite.lock()->transform->SetParent(WControl::UIHierarchy());
		logoSprite.lock()->transform->SetPosition(Vector2f(0, -350));
		NormalSprites2.push_back(logoSprite);
	}
	if (texture.loadFromFile(path + "Play" + ".png", IntRect(0, 0, 250, 65))) {
		Texture* newTexture = new Texture(texture);
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), VIEW_SIZE);
		texture.setSmooth(true);
		weak_ptr<ClickableSprite> wp = Instantiate<PlayButton>();
		wp.lock()->transform->renderBox.setTexture(newTexture);
		wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetPosition(Vector2f(0, -100));
		clickableSprites.push_back(wp);
		playButton =  dynamic_pointer_cast<PlayButton>(wp.lock());
	}
	if (texture.loadFromFile(path + "Score" + ".png", IntRect(0, 0, 250, 65))) {
		Texture* newTexture = new Texture(texture);
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), VIEW_SIZE);
		texture.setSmooth(true);
		weak_ptr<ClickableSprite> wp = Instantiate<ScoreButton>();
		wp.lock()->transform->renderBox.setTexture(newTexture);
		wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetPosition(Vector2f(0, 0));
		clickableSprites.push_back(wp);
		scoreButton = dynamic_pointer_cast<ScoreButton>(wp.lock());;
	}
	if (texture.loadFromFile(path + "Toolkit" + ".png", IntRect(0, 0, 250, 65))) {
		Texture* newTexture = new Texture(texture);
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), VIEW_SIZE);
		texture.setSmooth(true);
		weak_ptr<ClickableSprite> wp = Instantiate<ToolkitButton>();
		wp.lock()->transform->renderBox.setTexture(newTexture);
		wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetPosition(Vector2f(0, 100));
		clickableSprites.push_back(wp);
		toolkitButton = dynamic_pointer_cast<ToolkitButton>(wp.lock());;
	}
	if (texture.loadFromFile(path + "Setting" + ".png", IntRect(0, 0, 250, 65))) {
		Texture* newTexture = new Texture(texture);
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), VIEW_SIZE);
		texture.setSmooth(true);
		weak_ptr<ClickableSprite> wp = Instantiate<SettingButton>();
		wp.lock()->transform->renderBox.setTexture(newTexture);
		wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetPosition(Vector2f(0, 200));
		clickableSprites.push_back(wp);
		settingButton = dynamic_pointer_cast<SettingButton>(wp.lock());
	}
	if (texture.loadFromFile(path + "Exit" + ".png", IntRect(0, 0, 250, 65))) {
		Texture* newTexture = new Texture(texture);
		SpriteOffsetData spriteOffsetData(Vector2i(0, 0), Vector2i(250, 65), Vector2f(250, 65), Vector2f(0, 0), Vector2f(0, 0), VIEW_SIZE);
		texture.setSmooth(true);
		weak_ptr<ClickableSprite> wp = Instantiate<ExitButton>();
		wp.lock()->transform->renderBox.setTexture(newTexture);
		wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetPosition(Vector2f(0, 300));
		clickableSprites.push_back(wp);
		exitButton = dynamic_pointer_cast<ExitButton>(wp.lock());
	}
	{
		weak_ptr<GameSprite> wp = Instantiate<GameSprite>();
		wp.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		wp.lock()->transform->SetParent(WControl::UIHierarchy());
		wp.lock()->transform->SetSize(Vector2f(1920, 1080), RenderBox);
		wp.lock()->transform->renderBox.setFillColor(Color::Black);
		NormalSprites.push_back(wp);
	}
}

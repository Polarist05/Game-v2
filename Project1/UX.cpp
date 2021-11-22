#include "UX.h"
#include "WorldControl.h"
#include "Player.h"
UX::UX()
{
	{
		std::string path = "Sprites\\UX\\";
		keyTexture[0].loadFromFile(path + "Key_Empty" + ".png", IntRect(0, 0, 250, 250));
		keyTexture[1].loadFromFile(path + "Key_Fill" + ".png", IntRect(0, 0, 250, 250));
		soulTexture[0].loadFromFile(path + "Soul_Empty" + ".png", IntRect(0, 0, 250, 250));
		soulTexture[1].loadFromFile(path + "Soul_Fill" + ".png", IntRect(0, 0, 250, 250));
		keyTexture[0].setSmooth(true);
		keyTexture[1].setSmooth(true);
		soulTexture[0].setSmooth(true);
		soulTexture[1].setSmooth(true);
	}
	{
		SpriteOffsetData spriteOffsetData(Vector2i(38, 22), Vector2i(193, 204), Vector2f(193, 204), Vector2f(0, 0), Vector2f(0, 0), 0.5);
		for (size_t i = 0; i < KEY_AMOUNT; i++)
		{
			keys.push_back(Instantiate<GameSprite>("KeyUX"));
			weak_ptr<GameSprite> wp = keys[keys.size() - 1];
			wp.lock()->transform->renderBox.setTexture(&keyTexture[0]);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UXPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Multiple(WControl::view().getSize(), Vector2f(0.5, -0.5)) + Vector2f((-80. * i) - 60., 70));
		}
	}
	{
		SpriteOffsetData spriteOffsetData(Vector2i(15, 15), Vector2i(219, 219), Vector2f(219, 219), Vector2f(0, 0), Vector2f(0, 0), 0.4);
		for (size_t i = 0; i < SOUL_AMOUNT; i++)
		{
			souls.push_back(Instantiate<GameSprite>("SoulUX"));
			weak_ptr<GameSprite> wp = souls[souls.size() - 1];
			wp.lock()->transform->renderBox.setTexture(&soulTexture[1]);
			wp.lock()->transform->SetAllSpriteOffset(spriteOffsetData);
			wp.lock()->transform->RenderPriority = RenderPriorityType::UXPriority;
			wp.lock()->transform->SetParent(WControl::UIHierarchy());
			wp.lock()->transform->SetPosition(Multiple(WControl::view().getSize(), Vector2f(-0.5, -0.5)) + Vector2f(90. * i + 60., 60));
		}
	}
	{
		Vector2f position = Multiple(WControl::view().getSize(), Vector2f(0.5, 0.5)) + Vector2f(-150, -50);
		score.SetParent(WControl::UIHierarchy());
		score.SetPosition(position);
		
		scoreHighlight.setSize(Multiple((Vector2f)WControl::TextOffsetData().renderPixelSize, Vector2f(10, 1)) + Vector2f(20, 10));
		scoreHighlight.setOrigin(Multiple(scoreHighlight.getSize(),Vector2f(0.5,0.5)));
		scoreHighlight.setFillColor(Color::Blue);
	}
	{
		Vector2f position = Multiple(WControl::view().getSize(), Vector2f(-0.5, 0.5)) + Vector2f(150, -50);
		runTime.SetParent(WControl::UIHierarchy());
		runTime.SetPosition(position);

		runTimeHighlight.setSize(Multiple((Vector2f)WControl::TextOffsetData().renderPixelSize, Vector2f(10, 1)) + Vector2f(20, 10));
		runTimeHighlight.setOrigin(Multiple(runTimeHighlight.getSize(), Vector2f(0.5, 0.5)));
		runTimeHighlight.setFillColor(Color::Blue);
	}
}

void UX::Update()
{
	SetSoul(WControl::player().lock()->GetSoul());
	SetKey(WControl::player().lock()->GetKey());
	score.SetText("Score "+ to_string(WControl::player().lock()->GetScore()));
	int second = (Mode::playMode()->getRunTime() / 1000);
	int minuite = second / 60;
	runTime.SetText("Time " +to_string((minuite / 10) % 10)+to_string(minuite%10)  + ':' + to_string((second / 10)%6)+to_string(second % 10) );
	scoreHighlight.setPosition(WControl::GetCurrentRoom().lock()->MiddlePositionOfRoom()+ score.GetPosition());
	runTimeHighlight.setPosition(WControl::GetCurrentRoom().lock()->MiddlePositionOfRoom() + runTime.GetPosition());
}

void UX::SetSoul(const int& amount)
{
	if (amount > souls.size()) {
		printf("Input soul amount higher than max\n");
		return;
	}
	int i = 0;
	for (; i < amount; i++) {
		souls[i].lock()->transform->renderBox.setTexture(&soulTexture[1]);
	}
	for (;i<souls.size();i++) {
		souls[i].lock()->transform->renderBox.setTexture(&soulTexture[0]);
	}
}

void UX::SetKey(const int& amount)
{
	if (amount > keys.size()) {
		printf("Input key amount higher than max\n");
		return;
	}
	int i = 0;
	for (; i < amount; i++) {
		keys[i].lock()->transform->renderBox.setTexture(&keyTexture[1]);
	}
	for (; i < keys.size(); i++) {
		keys[i].lock()->transform->renderBox.setTexture(&keyTexture[0]);
	}
}

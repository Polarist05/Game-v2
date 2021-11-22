#include "EndGameUI.h"
#include "WorldControl.h"
void EndGameUI::StartScoreBoard()
{
	positionInScoreboard = -1;
	int score = WControl::player().lock()->GetScore();
	for (int i=0;i<5;i++) {
		if (WControl::scoreboard()[i].second < score) {
			for (int j = i + 1; j < 5; j++) {
				WControl::scoreboard()[j].first= WControl::scoreboard()[j - 1].first;
				WControl::scoreboard()[j].second = WControl::scoreboard()[j - 1].second;
			}
			WControl::scoreboard()[i].first = WControl::playerName();
			WControl::scoreboard()[i].second = score;
			positionInScoreboard = i;
			score = -1;
		}
		leaderBoardNameText[i].SetText(WControl::scoreboard()[i].first);
		leaderBoardScoreText[i].SetText(to_string(WControl::scoreboard()[i].second));
	}
	Load::SaveScoreboard();
}
void EndGameUI::UpdateName()
{
	if (positionInScoreboard != -1) {
		WControl::scoreboard()[positionInScoreboard].first = WControl::playerName();
		leaderBoardNameText[positionInScoreboard].SetText(WControl::playerName());
		Load::SaveScoreboard();
	}
}
EndGameUI::EndGameUI()
{
	{
		nameText.SetParent(WControl::UIHierarchy());
		nameText.SetPosition(Vector2f(-100, -100));
		nameText.SetText("RUN TEST");
		for (auto& wp : nameText.getSprites()) {
			NormalSprites2.push_back(wp);
		}

		nameWord.SetParent(WControl::UIHierarchy());
		nameWord.SetPosition(Vector2f(-100, -170));
		nameWord.SetText("name");
		for (auto& wp : nameWord.getSprites()) {
			NormalSprites2.push_back(wp);
		}
	}
	{
		scoreText.SetParent(WControl::UIHierarchy());
		scoreText.SetPosition(Vector2f(100+20, -100));
		scoreText.SetText("123456"); //to_string(WControl::player().lock()->GetScore())
		for (auto& wp : scoreText.getSprites()) {
			NormalSprites2.push_back(wp);
		}

		scoreWord.SetParent(WControl::UIHierarchy());
		scoreWord.SetPosition(Vector2f(100+20, -170));
		scoreWord.SetText("Score"); //to_string(WControl::player().lock()->GetScore())
		for (auto& wp : scoreWord.getSprites()) {
			NormalSprites2.push_back(wp);
		}
	}

	{
		background = Instantiate<GameSprite>("backGround");
		background.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		background.lock()->transform->SetParent(WControl::UIHierarchy());
		background.lock()->transform->SetSize(Vector2f(1920, 1080), RenderBox);
		background.lock()->transform->renderBox.setFillColor(Color::Black);
		NormalSprites.push_back(background);
	}
	{
		table1 = Instantiate<GameSprite>("table1");
		table1.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		table1.lock()->transform->SetParent(WControl::UIHierarchy());
		table1.lock()->transform->SetSize(Vector2f(600, 500), RenderBox);
		table1.lock()->transform->SetPosition(Vector2f(0, 200));
		table1.lock()->transform->renderBox.setFillColor(MyColor::gray());
		NormalSprites.push_back(table1);
	}
	{
		table2 = Instantiate<GameSprite>("table2");
		table2.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		table2.lock()->transform->SetParent(WControl::UIHierarchy());
		table2.lock()->transform->SetSize(Vector2f(600, 70), RenderBox);
		table2.lock()->transform->SetPosition(Vector2f(0, -100));
		table2.lock()->transform->renderBox.setFillColor(Color::Magenta);
		NormalSprites.push_back(table2);
	}
	{
		table3 = Instantiate<GameSprite>("table3");
		table3.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		table3.lock()->transform->SetParent(WControl::UIHierarchy());
		table3.lock()->transform->SetSize(Vector2f(600, 50), RenderBox);
		table3.lock()->transform->SetPosition(Vector2f(0, -170));
		table3.lock()->transform->renderBox.setFillColor(Color::Blue);
		NormalSprites.push_back(table3);
	}

	{
		ChangeNameButton = Instantiate<ChangeRunNameButton>("Change name Button");
		ChangeNameButton.lock()->transform->RenderPriority = RenderPriorityType::UIPriority;
		ChangeNameButton.lock()->transform->SetParent(WControl::UIHierarchy());
		ChangeNameButton.lock()->transform->SetSize(Multiple((Vector2f)WControl::TextOffsetData().renderPixelSize, Vector2f(10.5, 1)), RenderBox);
		ChangeNameButton.lock()->transform->renderBox.setTexture(&WControl::otherPrefab()["TaskBar"]);
		ChangeNameButton.lock()->transform->SetPosition(Vector2f(-100, -100));
		clickableSprites.push_back(dynamic_pointer_cast<ChangeRunNameButton>(ChangeNameButton.lock()));
	}
	for (auto& text : leaderBoardNameText) {
		size_t index = &text - &leaderBoardNameText[0];
		text.SetParent(WControl::UIHierarchy());
		text.SetPosition(Vector2f(-100, 100 * index));
		text.SetText("Name" + to_string(index));
		for (auto& wp : text.getSprites())
		{
			NormalSprites2.push_back(wp);
		}
	}
	for (auto& text : leaderBoardScoreText) {
		size_t index = &text - &leaderBoardScoreText[0];
		text.SetParent(WControl::UIHierarchy());
		text.SetPosition(Vector2f(100+20, 100 * index));
		text.SetText("Score " + to_string(index));
		for (auto& wp : text.getSprites())
		{
			NormalSprites2.push_back(wp);
		}
	}

}

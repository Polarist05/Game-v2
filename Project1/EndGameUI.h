#pragma once
#include "UI.h"
#include "TextUI.h"
#include <array>
#include "ChangeRunNameButton.h"
class EndGameUI:public UI
{
	std::array<TextUI, 5> leaderBoardScoreText;
	std::array<TextUI, 5> leaderBoardNameText;
	int positionInScoreboard;
public:	
	void StartScoreBoard();
	void UpdateName();
	bool isEditingName = false;
	EndGameUI();
	TextUI nameText,nameWord;
	TextUI scoreText,scoreWord;
	weak_ptr<ChangeRunNameButton> ChangeNameButton;
	weak_ptr<GameSprite> background,table1, table2,table3;
};

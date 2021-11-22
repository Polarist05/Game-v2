#include "EndGameMode.h"
#include "GameRenderer.h"
#include "WorldControl.h"
#include "Update.h"
#include "KeyPress.h"
void EndGameMode::CheckKeyPress()
{
	static char holdc;
	if (ALLUI::endGameUI().isEditingName) {
		static time_t delay = 0;
		{
			char c = KeyPress::CheckAlphaBetOrNumberKey();
			if (holdc != c && c && WControl::playerName().size() < 10) {
				WControl::playerName().push_back(c);
				ALLUI::endGameUI().nameText.SetText(WControl::playerName());
			}
			holdc = c;
		}
		if (clock() > delay + 80) {
			delay = clock();
			if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
				if (!WControl::playerName().empty()) {
					WControl::playerName().pop_back();
					ALLUI::endGameUI().nameText.SetText(WControl::playerName());
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				if (!WControl::playerName().empty()) {
					ALLUI::endGameUI().nameText.SetColor(Color::White);
					ALLUI::endGameUI().isEditingName = false;
					ALLUI::endGameUI().UpdateName();
				}
			}
		}
	}
	KeyPress::CheckEscape();
	KeyPress::CheckClickableSprite();
}

void EndGameMode::RenderGame()
{
	GameRenderer::RenderUI();
}

void EndGameMode::SetUp()
{
	for (auto& a : WControl::sound())
		a.second.stop();
	WControl::music().stop();
	while (!WControl::UIStack().empty())
		WControl::UIStack().pop();
	WControl::UIStack().push(UIType::EndGamePage);
	ALLUI::endGameUI().nameText.SetText(WControl::playerName());
	ALLUI::endGameUI().scoreText.SetText(to_string(WControl::player().lock()->GetScore()));
	ALLUI::endGameUI().StartScoreBoard();
}

void EndGameMode::Update()
{
	Update::UpdateUI();
}

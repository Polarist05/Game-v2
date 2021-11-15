#include "ChangeRunNameButton.h"
#include "WorldControl.h"
ChangeRunNameButton::ChangeRunNameButton():ClickableSprite(){}

ChangeRunNameButton::ChangeRunNameButton(std::string s):ClickableSprite(s){}

void ChangeRunNameButton::Activate()
{
	
	ALLUI::endGameUI().nameText.SetColor(Color::Cyan);
	ALLUI::endGameUI().isEditingName = true;
}

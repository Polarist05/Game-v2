#pragma once
#include "UI.h"
#include "ExitButton.h"
#include "PlayButton.h"
#include "ScoreButton.h"
#include "SettingButton.h"
#include "ToolkitButton.h"
class StartUI:public UI
{
public:
	StartUI();
	weak_ptr<ExitButton> exitButton;
	weak_ptr<PlayButton> playButton;
	weak_ptr<ScoreButton> scoreButton;
	weak_ptr<SettingButton> settingButton;
	weak_ptr<ToolkitButton> toolkitButton;

};


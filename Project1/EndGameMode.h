#pragma once
#include "GameMode.h"
class EndGameMode:public GameMode
{
public:
	void CheckKeyPress() override;
	void RenderGame() override;
	void SetUp() override;
	void Update() override;
};


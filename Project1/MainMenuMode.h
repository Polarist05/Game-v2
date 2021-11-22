#pragma once
#include "GameMode.h"
class MainMenuMode :public GameMode
{
public:
	void Start()override;
	void Update()override;
	void CheckKeyPress()override;
	void RenderGame() override;
	void SetUp() override;
};


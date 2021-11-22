#pragma once
#include "GameMode.h"
class PauseMode :public GameMode
{
public:
	void Start()override;
	void Update()override;
	void CheckKeyPress()override;
	void RenderGame() override;
};


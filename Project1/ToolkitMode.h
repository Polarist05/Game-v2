#pragma once
#include "GameMode.h"
class ToolkitMode:public GameMode
{
public:
	void Start() override;
	void Update()override;
	void CheckKeyPress() override;
	void RenderGame() override;
};


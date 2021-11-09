#pragma once
#include "GameBaseClass.h"
#include "KeyPress.h"
#include "GameRenderer.h"
class GameMode :public GameBaseClass
{
public:
	virtual void CheckKeyPress() {}
	virtual void RenderGame() {};
	virtual void SetUp() {};
};


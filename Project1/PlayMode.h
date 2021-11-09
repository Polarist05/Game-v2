#pragma once
#include "GameMode.h"
class PlayMode:public GameMode
{
	time_t runTime;
	time_t lastFrameTime;
public :
	void Start() override;
	void SetUp() override;
	void Update()override;
	void CheckKeyPress() override;
	void RenderGame() override;
	time_t getRunTime();
};


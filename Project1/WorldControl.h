#pragma once
#pragma once
#include "SFML.h"
#include "GameBaseClass.h"
class WorldControl:public GameBaseClass {
public:
	static RenderWindow& window();
	static float WorldScale();
	//static weak_ptr<GameSprite>& Hierarchy();
};
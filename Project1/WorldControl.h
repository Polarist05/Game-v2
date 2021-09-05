#pragma once
#pragma once
#include "SFML.h"
#include "GameBaseClass.h"
#include "GameSprite.h"
class WorldControl:public GameBaseClass {
public:
	static RenderWindow& window();
	static float WorldScale();
};
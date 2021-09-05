#pragma once
#pragma once
#include "SFML.h"
#include "GameBaseClass.h"
#include <memory>
#include <vector>
using namespace std;
enum AnchorType
{
	TopLeft,
	TopCentor,
	TopRight,
	MiddleLeft,
	MiddleCentor,
	MiddleRight,
	DownLeft,
	DownCentor,
	DownRight,
};
class GameSprite;
weak_ptr<GameSprite>& f1();
class WorldControl;
class GameTransform
{
private:
	weak_ptr<GameSprite> Hierachy();
	bool CheckGameTransfromInitialize();
public:

	type_index typeIndex = type_index(typeid(int));
	weak_ptr<GameSprite> root;
	weak_ptr<GameSprite> parent;
	vector<weak_ptr<GameSprite> > childs;
	weak_ptr<GameSprite> wp;
	RectangleShape hitBox;
	RectangleShape spriteBox;
	void SetParent(weak_ptr<GameSprite>);
	//int anchorType = AnchorType::MiddleCentor;
	//bool fixWidth = true;
	Vector2f scale = Vector2f(1.0, 1.0);
	//void SetScale(float x, float y);
	//void SetPosition(float x, float y);
	//void SetAnchorType(AnchorType _anchor);
	GameTransform();
	GameTransform(weak_ptr<GameSprite> wp, type_index typeIndex);
	~GameTransform();
};
class GameSprite :public GameBaseClass
{
public:
	GameTransform transform;
	weak_ptr<GameSprite> wp();
};







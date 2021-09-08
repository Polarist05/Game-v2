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
	DownRight
};
enum BoxType
{
	RenderBox,
	HitBox,
	SpriteBox
};
class GameSprite :public GameBaseClass
{
protected:
	class GameTransform
	{
	private:
		weak_ptr<GameSprite> Hierachy();
		Vector2f DistantFromMiddleCenter(RectangleShape& rect,Vector2f v);
	public:
		int childIndex=0;
		type_index typeIndex = type_index(typeid(int));
		weak_ptr<GameSprite> root;
		weak_ptr<GameSprite> parent;
		vector<weak_ptr<GameSprite> > childs;
		weak_ptr<GameSprite> wp;
		RectangleShape hitBox;
		RectangleShape renderBox;
		RectangleShape spriteBox;
		void SetParent(weak_ptr<GameSprite>);
		int anchorType = AnchorType::MiddleCentor;
		bool fixWidth = true;
		Vector2f position;
		Vector2f OffsetHitBox = Vector2f(0, 0);
		Vector2f OffsetRenderBox = Vector2f(0, 0);
		Vector2f defaultOffsetHitBox = Vector2f(0,0);
		Vector2f defaultOffsetRenderBox = Vector2f(0, 0);
		Vector2f scale = Vector2f(1.0, 1.0);
		//void SetScale(float x, float y);
		void SetPosition(float x, float y);
		void SetAnchorType(AnchorType _anchor, BoxType boxType);
		~GameTransform();
	};
public:
	GameSprite();
	~GameSprite();
	GameSprite(std::string s);
	GameTransform transform;
	void SetTransform(weak_ptr<GameSprite> wp, type_index typeIndex);
	std::string name = "null";
};








#pragma once
#pragma once
#include "SFML.h"
#include "GameBaseClass.h"
#define FIX_ONLY_ANCHOR_POSITION 0
#define FIX_ALL_RECT_POSITION 1
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
enum RenderPriorityType
{
	Setting,
	UI,
	PlayerAndObject,
	Knife,
	Floor
};
enum BoxType
{
	RenderBox,
	HitBox,
};
class GameSprite :public GameBaseClass
{
protected:
	class GameTransform
	{
	private:
		weak_ptr<GameSprite> Hierachy();
		void SetAnchorType(AnchorType _anchor, BoxType boxType, bool FIXTYPE);
	public:
		void SetSize(Vector2f v, BoxType boxType, bool FIXTYPE);
		int childIndex=0;
		int RenderPriority = 0;
		type_index typeIndex = type_index(typeid(int));
		weak_ptr<GameSprite> root;
		weak_ptr<GameSprite> parent;
		vector<weak_ptr<GameSprite> > childs;
		weak_ptr<GameSprite> wp;
		RectangleShape hitBox;
		RectangleShape renderBox;		
		AnchorType anchorType = AnchorType::MiddleCentor;
		Vector2f position;
		Vector2f OffsetHitBox = Vector2f(0, 0);
		Vector2f OffsetRenderBox = Vector2f(0, 0);
		Vector2f scale = Vector2f(1,1);
		void SetScale(Vector2f v);
		void virtual SetParent(weak_ptr<GameSprite>);
		void virtual SetPosition(float x, float y);
		void virtual SetPosition(Vector2f v);
		void SetPosition(Vector2f v, BoxType boxType);
		void SetAnchorType(AnchorType _anchor, BoxType boxType);
		void Move(Vector2f v, BoxType boxType);
		void virtual Move(Vector2f v);
		GameTransform();
		GameTransform(Vector2f position, Vector2f scale, Vector2f hitboxPosition, Vector2f renderPosition);
		~GameTransform();
		virtual void Printing();
	};
private:
	GameTransform m_transform;
public:
	GameSprite();
	~GameSprite();
	GameSprite(std::string s);
	/*NotUseNow
	GameSprite(std::string s,Vector2f position,Vector2f scale,Vector2f hitboxPosition,Vector2f renderPosition);
	GameSprite(std::string s,Vector2f position, Vector2f scale);
	GameSprite(GameSprite& gameSprite);
	*/
	GameTransform* transform = &m_transform;
	void virtual SetTransform(weak_ptr<GameSprite> wp, type_index typeIndex);
	std::string name = "null";
};
void MoveAndDrawAllSprites(weak_ptr<GameSprite> a, int b, Vector2f position, Vector2f realWorldScale);
void MoveAllSprites(weak_ptr<GameSprite> a, int b, Vector2f position, Vector2f realWorldScale);
void DrawAllSprites(weak_ptr<GameSprite> a );







#pragma once
#pragma once
#include "SFML.h"
#include "GameBaseClass.h"
#define FIX_ONLY_ANCHOR_POSITION 0
#define FIX_ALL_RECT_POSITION 1
using namespace std;
enum Direction
{
	Up,
	Down,
	Right,
	Left
};
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
	UIPriority,
	PlayerAndObject,
	KnifeType,
	Floor
};
enum BoxType
{
	RenderBox,
	PseudoRenderBox,
	HitBox
};
struct SpriteOffsetData {
	Vector2i renderPixelSize, startPixel;
	Vector2f hitBoxSize, hitboxOffset, allOffset;
	float scale;
	SpriteOffsetData(const Vector2i& startPixel, const Vector2i& renderPixelSize, const Vector2f hitBoxSize, const Vector2f& hitboxOffset, const Vector2f& allOffset, const float& scale);
};
class GameSprite :public GameBaseClass
{
protected:
	class GameTransform
	{
	private:
		weak_ptr<GameSprite> Hierachy();
		void SetAnchorType(const AnchorType& _anchor,const BoxType& boxType);
	public:
		int childIndex=0;
		int RenderPriority = 0;
		type_index typeIndex = type_index(typeid(int));
		weak_ptr<GameSprite> root;
		weak_ptr<GameSprite> parent;
		vector<weak_ptr<GameSprite> > childs;
		weak_ptr<GameSprite> wp;
		
		RectangleShape hitBox;
		Vector2f OffsetHitBox = Vector2f(0, 0);
		AnchorType hitBoxAnchorType = MiddleCentor;

		RectangleShape renderBox;
		Vector2f OffsetRenderBox = Vector2f(0, 0);
		AnchorType renderBoxAnchorType = MiddleCentor;

		RectangleShape pseudoRenderBox;
		Vector2f OffsetPseudoRenderBox = Vector2f(0, 0);
		AnchorType pseudoRenderBoxAnchorType = MiddleCentor;

		Vector2f position;
		
		void virtual SetParent(weak_ptr<GameSprite>);
		void SetSize(const Vector2f& boxSize, const BoxType& boxType);
		
		void virtual SetPosition(float x, float y);
		void virtual SetPosition(Vector2f v);
		Vector2f GetRealposition();
		void SetPositionOffset(Vector2f v, BoxType boxType);
		void SetAllSpriteOffset(const SpriteOffsetData& spriteOffsetData);
		void SetAllSpriteOffset(const SpriteOffsetData& spriteOffsetData,const Vector2f& scale);
		void MoveOffset(const Vector2f& v,const BoxType& boxType);
		void virtual Move(Vector2f v);

		void SetAnchorType(AnchorType _anchor, BoxType boxType, bool FIXTYPE);
		
		~GameTransform();
	};
private:
	GameTransform m_transform;
public:
	GameSprite();
	~GameSprite();
	GameSprite(std::string s);
	GameTransform* transform = &m_transform;
	void virtual SetTransform(weak_ptr<GameSprite> wp, type_index typeIndex);
	
	std::string name = "null";
};

void MoveAllSprites(weak_ptr<GameSprite> a, int b, Vector2f position, Vector2f realWorldScale);







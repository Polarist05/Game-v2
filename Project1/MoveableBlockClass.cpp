#include "MoveableBlockClass.h"
#include "WorldControl.h"
bool MoveableBlockClass::PushBlock(const Direction& direction)
{
	if (!isMove) {
		switch (direction)
		{
		case Left:
			
			if (blockPosition.x - 1 > 0 && !WControl::GetCurrentRoom().lock()->cannotPush[blockPosition.y][blockPosition.x - 1]) {
				printf("Left\n");
				WControl::GetCurrentRoom().lock()->cannotPush[blockPosition.y][blockPosition.x] = false;
				blockPosition += Vector2i(-1, 0);
				velocity = Vector2f(-10, 0);
				lastPosition = WControl::GetCurrentRoom().lock()->GetTransform()->GetRealPositionAt(blockPosition);
				WControl::GetCurrentRoom().lock()->cannotPush[blockPosition.y][blockPosition.x] = true;
				//GetTransform()->SetPositionInTilemap(blockPosition);
				isMove = true;
			}
			break;
		case Right:
			if (blockPosition.x + 1 <= RSIZEX && !WControl::GetCurrentRoom().lock()->cannotPush[blockPosition.y][blockPosition.x + 1]) {
				printf("Right\n");
				WControl::GetCurrentRoom().lock()->cannotPush[blockPosition.y][blockPosition.x] = false;
				blockPosition += Vector2i(1, 0);
				velocity = Vector2f(10, 0);
				lastPosition = WControl::GetCurrentRoom().lock()->GetTransform()->GetRealPositionAt(blockPosition);
				WControl::GetCurrentRoom().lock()->cannotPush[blockPosition.y][blockPosition.x] = true;
				//GetTransform()->SetPositionInTilemap(blockPosition);
				
				isMove = true;
			}
			break;
		case Up:
			if (blockPosition.y - 1 > 0 && !WControl::GetCurrentRoom().lock()->cannotPush[blockPosition.y - 1][blockPosition.x]) {
				printf("Up\n");
				WControl::GetCurrentRoom().lock()->cannotPush[blockPosition.y][blockPosition.x] = false;
				blockPosition += Vector2i(0, -1);
				velocity = Vector2f(0, -10);
				lastPosition = WControl::GetCurrentRoom().lock()->GetTransform()->GetRealPositionAt(blockPosition);
				WControl::GetCurrentRoom().lock()->cannotPush[blockPosition.y][blockPosition.x] = true;
				//GetTransform()->SetPositionInTilemap(blockPosition );
				
				isMove = true;
			}
			break;
		case Down:
			if (blockPosition.y + 1 <= RSIZEY && !WControl::GetCurrentRoom().lock()->cannotPush[blockPosition.y + 1][blockPosition.x]) {
				printf("Down\n");
				WControl::GetCurrentRoom().lock()->cannotPush[blockPosition.y][blockPosition.x] = false;
				blockPosition += Vector2i(0, 1);
				velocity = Vector2f(0, 10);
				lastPosition = WControl::GetCurrentRoom().lock()->GetTransform()->GetRealPositionAt(blockPosition);
				WControl::GetCurrentRoom().lock()->cannotPush[blockPosition.y][blockPosition.x] = true;
				//GetTransform()->SetPositionInTilemap(blockPosition);
				isMove = true;
			}
			break;
		default:
			break;
		}
		return true;
	}
	else
		return false;
}

void MoveableBlockClass::SetPosition(const Vector2i& v) { blockPosition = v; }

MoveableBlockClass::MoveableBlockClass():Area(){}

MoveableBlockClass::MoveableBlockClass(std::string s):Area(s){}

void MoveableBlockClass::interacting(weak_ptr<Knife> knife)
{
	Vector2f newPos = knife.lock()->transform->GetRealposition() - transform->GetRealposition();
	knife.lock()->transform->position = newPos;
	knife.lock()->transform->SetParent(transform->wp);
	knife.lock()->Stop();
}

void MoveableBlockClass::Update()
{
	if (isMove) {
		Vector2f distance2f = transform->GetRealposition() - lastPosition;
		float distance = sqrt(distance2f.x * distance2f.x + distance2f.y * distance2f.y) ;
		if (distance < 10) {
			GetTransform()->SetPositionInTilemap(GetTransform()->GetPositionInTilemap()+Vector2i(velocity.x?velocity.x / abs(velocity.x):0, velocity.y? velocity.y /abs(velocity.y) :0));
			isMove = false;
		}
		else {
			transform->position += velocity;
		}
	}
}

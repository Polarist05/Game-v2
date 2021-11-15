#include "ObjectDropDown.h"
#include "WorldControl.h"
#include "ToolkitUI.h"
void ClearObject(Vector2i pos) {}
void InstantChargeSoul(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantChargeSoul(pos); }
void InstantBell(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantBell(pos); }
void InstantHook(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantHook(pos); }
void InstantPortal(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantPortal(pos); }
void InstantStrawberry(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantStrawberry(pos); }
void InstantMovingPlatform(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantMovingPlatform(pos); }
void InstantSwitch(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantSwitch(pos); }
void InstantNormalBlock(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantNormalBlock(pos); }
void InstantDeleteBlock(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantDeleteBlock(pos); }
void InstantSignalBlock(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantSignalBlock(pos); }
void InstantMoveableBlock(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantMoveableBlock(pos); }
void InstantPlacingSwitch(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantPlacingSwitch(pos); }
void InstantLaser(Vector2i pos) { WControl::GetCurrentRoom().lock()->InstantLaser(pos); }

void ObjectDropDown::Activate()
{
	ToolkitUI& thisUI = ALLUI::toolkitUI();
	for (auto& x : WControl::GetChosedAreaPosition()) {
		for (auto& y : x.second) {
			if (!WControl::GetCurrentRoom().lock()->Space[y - 1][x.first - 1].expired()) {
				auto wp=WControl::GetCurrentRoom().lock()->Space[y - 1][x.first - 1].lock()->transform->wp;
				auto index = WControl::GetCurrentRoom().lock()->Space[y - 1][x.first - 1].lock()->transform->typeIndex;
				Destroy(wp,index);
			}
			func(Vector2i(x.first, y));
			thisUI.newRoomData.objects[y-1][x.first-1]=saveInt;
		}
	}
		
}
void ObjectDropDown::SetType(const ObjectType& obj)
{
	switch (obj)
	{
	case Null:
		func = ClearObject;
		saveInt=0;
		break;
	case ChargeSoul:
		func = InstantChargeSoul;
		saveInt = 10;
		break;
	case Bell:
		func = InstantBell;
		saveInt = 20;
		break;
	case Hook:
		func=InstantHook;
		saveInt = 30;
		break;
	case Portal:
		func = InstantPortal;
		saveInt = 40;
		break;
	case Strawberry:
		func = InstantStrawberry;
		saveInt = 50;
		break;
	case MovingPlatform:
		func = InstantMovingPlatform;
		saveInt = 60;
		break;
	case Switch:
		func = InstantSwitch;
		saveInt = 70;
		break;
	case NormalBlock:
		func = InstantNormalBlock;
		saveInt = 80;
		break;
	case DeleteBlock:
		func = InstantDeleteBlock;
		saveInt = 90;
		break;
	case SignalBlock:
		func = InstantSignalBlock;
		saveInt = 100;
		break;
	case MoveableBlock:
		func = InstantMoveableBlock;
		saveInt = 110;
		break;
	case PlacingSwitch:
		func = InstantPlacingSwitch;
		saveInt = 120;
		break;
	case Laser:
		func = InstantLaser;
		saveInt = 130;
		break;
	}
}


#include "PortalClass.h"
#include "WorldControl.h"
PortalClass::PortalClass() :Area() {}
PortalClass::PortalClass(std::string s):Area(s) {}
void PortalClass::WalkThroughActivate() {
	if (!pairPortal.expired()) {
		if (clock() - lastCollisionTime>50) {
			WControl::player().lock()->transform->position += pairPortal.lock()->GetTransform()->position-GetTransform()->position;
		}
		lastCollisionTime = clock();
		pairPortal.lock()->lastCollisionTime = clock();
	}
}
bool PortalClass::Linking(weak_ptr<PortalClass> pairPortal) {
	if (!pairPortal.expired()) {
		this->pairPortal = pairPortal;
		return true;
	}
	else {
		return false;
	}
}
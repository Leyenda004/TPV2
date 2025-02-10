#include "Container.h"
#include "ShowAtOppositeSide.h"
#include "../sdlutils/sdlutils.h"

void ShowAtOppositeSide::update(Container* o) {
	if (o->getPos().getY() >= sdlutils().height()) {
		o->getPos().setY(0);
	}
	else if (o->getPos().getY() <= 0) {
		o->getPos().setY(sdlutils().height());
	}
	if (o->getPos().getX() >= sdlutils().width()) {
		o->getPos().setX(0);
	}
	else if (o->getPos().getX() <= 0) {
		o->getPos().setX(sdlutils().width());
	}
}
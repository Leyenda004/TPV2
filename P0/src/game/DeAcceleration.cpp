#include "DeAcceleration.h"
#include "Container.h"

void DeAcceleration::update(Container* o) {
	o->getVel() = o->getVel() * 0.995f;
}
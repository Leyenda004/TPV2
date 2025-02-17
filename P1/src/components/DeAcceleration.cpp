#include "DeAcceleration.h"

#include <cassert>

#include "../ecs/Manager.h"
//#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

void DeAcceleration::initComponent() {
	auto* mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void DeAcceleration::update() {
	if (_tr->getVel().magnitude() < 0.05f) {
		_tr->getVel() = Vector2D(0, 0);
	}
	else { _tr->getVel() = _tr->getVel() * 0.995f; }
}
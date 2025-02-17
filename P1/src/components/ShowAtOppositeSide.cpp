#include "ShowAtOppositeSide.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

void ShowAtOppositeSide::initComponent() {
	auto* mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void ShowAtOppositeSide::update() {
	// Esto esta mal!!!!!!!!
	if (_tr->getPos().getY() >= sdlutils().height()) {
		_tr->getPos().setY(0 - _tr->getHeight());
	}
	else if (_tr->getPos().getY() <= 0) {
		_tr->getPos().setY(sdlutils().height());
	}
	if (_tr->getPos().getX() >= sdlutils().width()) {
		_tr->getPos().setX(0 - _tr->getWidth());
	}
	else if (_tr->getPos().getX() <= 0) {
		_tr->getPos().setX(sdlutils().width());
	}
}
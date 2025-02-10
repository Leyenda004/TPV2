// This file is part of the course TPV2@UCM - Samir Genaim

#include "PaddleMouseCtrl.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"

PaddleMouseCtrl::PaddleMouseCtrl() :
		_tr(nullptr) {
}

PaddleMouseCtrl::~PaddleMouseCtrl() {
}

void PaddleMouseCtrl::initComponent() {
	auto mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void PaddleMouseCtrl::update() {
	auto &ihdlr = ih();

	auto &pos = _tr->getPos();

	if (ihdlr.mouseMotionEvent()) {
		pos.setY(ihdlr.getMousePos().second);
	}
}

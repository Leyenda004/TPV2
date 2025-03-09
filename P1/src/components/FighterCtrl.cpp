#include "FighterCtrl.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

void FighterCtrl::initComponent() {
	auto* mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void FighterCtrl::update() {
	handleInput();
}

void FighterCtrl::handleInput() {
	auto& ihdlr = ih();
	
	if (ihdlr.isKeyDown(SDLK_LEFT)) {
		std::cout << "rot left" << std::endl;
		_tr->setRot(_tr->getRot() - 5.0f);
	}
	else if (ihdlr.isKeyDown(SDLK_RIGHT)) {
		std::cout << "rot right" << std::endl;
		_tr->setRot(_tr->getRot() + 5.0f);
	}
	if (ihdlr.isKeyDown(SDLK_UP/*DUDA, SDL_ARROW_UP?*/)) {
		sdlutils().soundEffects().at("thrust").play();
		Vector2D newVel = _tr->getVel() + Vector2D(0, -1).rotate(_tr->getRot()) * thrust;

		if (newVel.magnitude() > speedLimit) {
			newVel = newVel.normalize() * speedLimit;
		}

		_tr->getVel() = newVel;

		std::cout << "vel = " << _tr->getVel().magnitude() << std::endl;
	}
}
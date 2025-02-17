#include "Container.h"
#include "../sdlutils/InputHandler.h" // duda: h o cpp?
#include "FighterCtrl.h"
// duda: implementar/declarar constructor y destructora vacios?

void FighterCtrl::handleInput(Container* o) {
	auto& ihdlr = ih();
	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(SDLK_LEFT)) {
			std::cout << "rot left" << std::endl;
			o->setRotation(o->getRotation() - 5.0f);
		}
		if (ihdlr.isKeyDown(SDLK_RIGHT)) {
			std::cout << "rot right" << std::endl;
			o->setRotation(o->getRotation() + 5.0f);
		}
		if (ihdlr.isKeyDown(SDLK_s)) {
			// !!!!!!!!
		}
		if (ihdlr.isKeyDown(SDLK_UP/*DUDA, SDL_ARROW_UP???*/)) {
			Vector2D newVel = o->getVel() + Vector2D(0, -1).rotate(o->getRotation()) * thrust;

			if (newVel.magnitude() > speedLimit) {
				newVel = newVel.normalize() * speedLimit;
			}

			o->getVel() = newVel;

			std::cout << "vel = " << o->getVel().magnitude() << std::endl;
		}
	}

	// duda: diferencia? buffer de verificacion de eventos?
	//if (ihdlr.isKeyDown(SDLK_LEFT)) {
	//std::cout << "rot left" << std::endl;
	//	o->setRotation(o->getRotation() + 5.0f);
	//}
	//else if (ihdlr.isKeyDown(SDLK_RIGHT)) {
	//std::cout << "rot right" << std::endl;
	//	o->setRotation(o->getRotation() - 5.0f);
	//}
}
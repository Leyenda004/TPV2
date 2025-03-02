#include "Gun.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

void Gun::initComponent() {
	auto* mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);

	_bulletTex = &sdlutils().images().at("bullet");

	assert(_tr != nullptr);
}

void Gun::update() {
	handleInput();

	for (auto& b : _bullets) {
		if (b.used) {
			b.pos = b.pos + b.vel;
		}
	}

}

void Gun::handleInput() {
	auto& ihdlr = ih();
	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(SDLK_s) && sdlutils().virtualTimer().currRealTime() >= nextShoot) {
			std::cout << "SHOOT" << std::endl;

			int bw = 5;
			int bh = 20;
			Vector2D c = _tr->getPos() + Vector2D(_tr->getWidth() / 2.0f, _tr->getHeight() / 2.0f);
			Vector2D bp = c - Vector2D(bw / 2, _tr->getHeight() / 2.0f + 5.0f + bh).rotate(_tr->getRot()) - Vector2D(bw / 2, bh / 2);
			Vector2D bv = Vector2D(0, -1).rotate(_tr->getRot()) * (_tr->getVel().magnitude() + 5.0f);
			float br = Vector2D(0, -1).angle(bv);

			shoot(bp/*body_position*/, bv/*body_vel*/, bw/*body_width*/, bh/*body_height*/, br/*body_rotation*/);

			nextShoot = sdlutils().virtualTimer().currRealTime() + 250;
		}
	}
}

void Gun::reset() {
	for (auto& b : _bullets) {
		b.used = false;
	}
}

void Gun::render() {

	std::cout << "[";
	for (Gun::Bullet& bala : _bullets) {
		assert(_bulletTex != nullptr);
		std::cout << (bala.used ? "1 " : "0 ");
		if (bala.used) {
			SDL_Rect dest = build_sdlrect(bala.pos, bala.width, bala.height);
			_bulletTex->render(dest, _tr->getRot());
		}
	}
	std::cout << "]" << std::endl;
}

void Gun::shoot(Vector2D p, Vector2D v, int width, int height, float r) {

	_bullets[itNum].used = true;

	for (auto i : _bullets) {
		if (!_bullets[itNum].used) {
			break;
		}
		itNum = (itNum + 1) % _max_bullets;
	}

	_bullets[itNum].pos = p;
	_bullets[itNum].vel = v;
	_bullets[itNum].width = width;
	_bullets[itNum].height = height;
	_bullets[itNum].rot = r;
}
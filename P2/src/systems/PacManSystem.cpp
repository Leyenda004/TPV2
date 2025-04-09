// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "ImmunitySystem.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Health.h"

PacManSystem::PacManSystem() :
		_pmTR(nullptr) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	// create the PacMan entity
	//
	auto pacman = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::PACMAN, pacman);

	_pmTR = _mngr->addComponent<Transform>(pacman);
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	_pmTR->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

	//_mngr->addComponent<Image>(pacman, &sdlutils().images().at("pacman"));

	sprite = _mngr->addComponent<ImageWithFrames>(pacman, &sdlutils().images().at("sprites"), 48, 8, 8);
	sprite->setFrame(1);

	health = _mngr->addComponent<Health>(pacman, 3);
}

void PacManSystem::update() {

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			_pmTR->_rot += 90.0f;
			_pmTR->_vel = _pmTR->_vel.rotate(90.0f);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			_pmTR->_rot -= 90.0f;
			_pmTR->_vel = _pmTR->_vel.rotate(-90.0f);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // speed
			float speed = 3.0f;
			_pmTR->_vel = Vector2D(0, -speed).rotate(_pmTR->_rot);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { // stop
			_pmTR->_vel = Vector2D(0, 0);
		}
	}

	// move the pacman
	_pmTR->_pos = _pmTR->_pos + _pmTR->_vel;

	// check left/right borders
	if (_pmTR->_pos.getX() < 0) {
		_pmTR->_pos.setX(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
	} else if (_pmTR->_pos.getX() + _pmTR->_width > sdlutils().width()) {
		_pmTR->_pos.setX(sdlutils().width() - _pmTR->_width);
		_pmTR->_vel.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (_pmTR->_pos.getY() < 0) {
		_pmTR->_pos.setY(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
	} else if (_pmTR->_pos.getY() + _pmTR->_height > sdlutils().height()) {
		_pmTR->_pos.setY(sdlutils().height() - _pmTR->_height);
		_pmTR->_vel.set(0.0f, 0.0f);
	}

}

void PacManSystem::onGhostCollides() {
	if (!_mngr->getSystem<ImmunitySystem>()->pacmanIsImmune()){
		// recibir mensaje en el estado
		if (health->vida > 0){
			health->healthUpdate(-1);

			Message m;
			m.id = _m_STATE_CHANGE;
			m.state_change_data.state = Game::NEWROUND;
			_mngr->send(m);
		}
		else{
			Message m;
			m.id = _m_STATE_CHANGE;
			m.state_change_data.state = Game::GAMEOVERBAD;
			_mngr->send(m);
		}
	}
}

void PacManSystem::recieve(const Message& m)
{
	switch (m.id) {
	case _m_PACMAN_GHOST_COLLISION:
		onGhostCollides();
		break;
	default:
		break;
	}
}
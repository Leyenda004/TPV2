// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../components/Milagrosa.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"

CollisionsSystem::CollisionsSystem() {
	// TODO Auto-generated constructor stub

}

CollisionsSystem::~CollisionsSystem() {
	// TODO Auto-generated destructor stub
}

void CollisionsSystem::initSystem() {
}

void CollisionsSystem::update() {

	checkCollisionInFruits();
	checkCollisionGhostPacman();
}

void CollisionsSystem::checkCollisionInFruits()
{
	// the PacMan's Transform
	//
	auto pm = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto pTR = _mngr->getComponent<Transform>(pm);

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	auto& food = _mngr->getEntities(ecs::grp::FOOD);
	auto n = food.size();

	for (auto i = 0u; i < n; i++)
	{
		auto e = food[i];
		if (_mngr->isAlive(e)) { // if the fruit is active (it might have died in this frame)

			// the Fruit's Transform
			//
			auto eTR = _mngr->getComponent<Transform>(e);

			// check if PacMan collides with the Fruit(i.e., eat it)
			if (Collisions::collides(			//
				pTR->_pos, pTR->_width, pTR->_height, //
				eTR->_pos, eTR->_width, eTR->_height)) {

				Milagrosa* miracl = _mngr->getComponent<Milagrosa>(e);

				Message m;
				m.id = _m_PACMAN_FOOD_COLLISION;
				m.food_eaten_data.e = e;
				m.food_eaten_data.miraculous = miracl->milagrosa && miracl->fruitChanged;
				_mngr->send(m);
			}
		}
	}
}

void CollisionsSystem::checkCollisionGhostPacman()
{
	// the PacMan's Transform
	//
	auto pm = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto pTR = _mngr->getComponent<Transform>(pm);

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	auto& ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
	auto n = ghosts.size();

	for (auto i = 0u; i < n; i++)
	{
		auto e = ghosts[i];
		if (_mngr->isAlive(e)) { // if the ghost is active (it might have died in this frame)

			// the Ghost's Transform
			//
			auto eTR = _mngr->getComponent<Transform>(e);

			// check if PacMan collides with the Ghost(i.e., eat it)
			if (Collisions::collides(			//
				pTR->_pos, pTR->_width, pTR->_height, //
				eTR->_pos, eTR->_width, eTR->_height)) {

				Message m;
				m.id = _m_PACMAN_GHOST_COLLISION;
				m.ghost_pacman_col_data.e = e;
				_mngr->send(m);
			}
		}
	}
}
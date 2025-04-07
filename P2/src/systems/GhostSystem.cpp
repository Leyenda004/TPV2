#include "GhostSystem.h"

#include "ImmunitySystem.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"

void GhostSystem::initSystem()
{
	pmTr = _mngr->getComponent<Transform>(_mngr->getHandler(ecs::hdlr::PACMAN));
	ghostSize = 40.0f;
}

void GhostSystem::update()
{
	if(!_mngr->getSystem<ImmunitySystem>()->pacmanIsImmune() &&
		sdlutils().virtualTimer().currTime() - lastInstanceTime > generationWaitTime
		&& _mngr->getEntities(ecs::grp::GHOSTS).size() < maxGhosts)
	{
		lastInstanceTime = sdlutils().virtualTimer().currTime();
		createGhost();
	}

	for (auto ghost : _mngr->getEntities(ecs::grp::GHOSTS))
	{
		Transform* gstTr = _mngr->getComponent<Transform>(ghost);

		if (sdlutils().rand().nextInt(0, 1000) < 5) // Random direction change to Pacman
		{
			gstTr->_vel = (pmTr->_pos - gstTr->_pos).normalize() * 1.1f;
		}

		gstTr->_pos = gstTr->_pos + gstTr->_vel;

		if (gstTr->_pos.getX() <= 0 || gstTr->_pos.getX() >= sdlutils().width() - ghostSize) // Border collision logic
		{
			gstTr->_vel.setX(gstTr->_vel.getX() * -1);
		}
		if (gstTr->_pos.getY() <= 0 || gstTr->_pos.getY() >= sdlutils().height() - ghostSize)
		{
			gstTr->_vel.setY(gstTr->_vel.getY() * -1);
		}

		if (sdlutils().virtualTimer().currTime() % 1000 == 0)
		{
			ImageWithFrames* gstFrames = _mngr->getComponent<ImageWithFrames>(ghost);

			if (_mngr->getSystem<ImmunitySystem>()->pacmanIsImmune())
			{
				 gstFrames->_frame = 48;
			}
			else
			{
				 gstFrames->_frame = 32;
			}
		}
		
	}
}

void GhostSystem::startGeneration()
{
	lastInstanceTime = sdlutils().virtualTimer().currTime();
}

void GhostSystem::createGhost()
{
	ecs::entity_t newGhost = _mngr->addEntity(ecs::grp::GHOSTS);

	Vector2D position, velocity;

	int cornerOp = sdlutils().rand().nextInt(0, 4);

	switch (cornerOp)
	{
		case 0: position = Vector2D(0, 0); break;
		case 1: position = Vector2D(sdlutils().width() - ghostSize, 0); break;
		case 2: position = Vector2D(0, sdlutils().height() - ghostSize); break;
		default: position = Vector2D(sdlutils().width() - ghostSize, sdlutils().height() - ghostSize); break;
	}
	
	if (position.getY() == 0) 
		velocity = Vector2D(0, 1);
	else 
		velocity = Vector2D(0, -1);

	Transform* tr = _mngr->addComponent<Transform>(newGhost);
	
	auto x = (sdlutils().width() - ghostSize) / 2.0f;
	auto y = (sdlutils().height() - ghostSize) / 2.0f;
	tr->init(position, velocity, ghostSize, ghostSize, 0.0f);

	ImageWithFrames* sprite = _mngr->addComponent<ImageWithFrames>(newGhost, &sdlutils().images().at("sprites"), 48, 8, 8);
	sprite->setFrame(32);
}

void GhostSystem::onPlayerCollides(ecs::entity_t e)
{
	_mngr->setAlive(e, false);

	//--_aliveFruits;

	//if (_aliveFruits <= 0)
	//{
	//	Message m;
	//	m.id = _m_GAME_OVER;
	//	m.game_over_data.playerWon = true;
	//	_mngr->send(m);
	//}
}

void GhostSystem::recieve(const Message& m)
{
	switch (m.id) {
	case _m_PACMAN_GHOST_COLLISION:
		onPlayerCollides(m.ghost_pacman_col_data.e);
		break;
	default:
		break;
	}
}
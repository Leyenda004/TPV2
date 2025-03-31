#include "GhostSystem.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"

void GhostSystem::initSystem()
{
	
}

void GhostSystem::update()
{
	if ((sdlutils().virtualTimer().currTime() / 1000) % 5 == 0 // Cada 5 segs
		&& _mngr->getEntities(ecs::grp::GHOSTS).size() < maxGhosts)
	{
		createGhost();
	}
}

void GhostSystem::startGeneration()
{
	initTime = sdlutils().virtualTimer().currTime();
}

void GhostSystem::createGhost()
{
	ecs::entity_t newGhost = _mngr->addEntity(ecs::grp::GHOSTS);

	Vector2D position, velocity;
	float size = 50.0f;

	int cornerOp = sdlutils().rand().nextInt(0, 4);

	switch (cornerOp)
	{
		case 0: position = Vector2D(0, 0); break;
		case 1: position = Vector2D(sdlutils().width() - size, 0); break;
		case 2: position = Vector2D(0, sdlutils().height() - size); break;
		default: position = Vector2D(sdlutils().width() - size, sdlutils().height() - size); break;
	}
	
	if (position.getX() == 0) 
		velocity = Vector2D(0, 1);
	else 
		velocity = Vector2D(0, -1);

	Transform* tr = _mngr->addComponent<Transform>(newGhost);
	
	auto x = (sdlutils().width() - size) / 2.0f;
	auto y = (sdlutils().height() - size) / 2.0f;
	tr->init(position, velocity, size, size, 0.0f);

	ImageWithFrames* sprite = _mngr->addComponent<ImageWithFrames>(newGhost, &sdlutils().images().at("sprites"), 48, 8, 8);
	sprite->setFrame(32);
}


#include "GhostSystem.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"

void GhostSystem::initSystem()
{
	auto pacman = _mngr->addEntity();
}

void GhostSystem::update()
{
	if ((sdlutils().virtualTimer().currTime() / 1000) % 5 == 0 // Cada 5 segs
		&& ghostsNum < maxGhosts) 
	{
		
	}

}

void GhostSystem::startGeneration()
{
	initTime = sdlutils().virtualTimer().currTime();
}

Vector2D GhostSystem::getRandomCornerPosition()
{
	return Vector2D();
}


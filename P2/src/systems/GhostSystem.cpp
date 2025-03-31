#include "GhostSystem.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

void GhostSystem::initSystem()
{
	auto pacman = _mngr->addEntity();
}

void GhostSystem::update()
{
	if (sdlutils().virtualTimer().currTime() - initTime % 5000 != 0) return;
	std::cout << 333 << "\n";
}

void GhostSystem::startGeneration()
{
	initTime = sdlutils().virtualTimer().currTime();
}

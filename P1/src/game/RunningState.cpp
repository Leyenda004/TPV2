#include "RunningState.h"

#include "Game.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "../sdlutils/InputHandler.h"
#include <SDL.h>

RunningState::RunningState()
{
	_mngr = Game::Instance()->getMngr();
	fighter = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER);
}

void RunningState::enter()
{

}

void RunningState::leave()
{

}

void RunningState::update()
{
	// TODO
	/*
	if(nAsteroids == 0)
	{
		Game::Instance()->setState(Game::GameOverState);
		return;
	}
	*/
	if(ih().isKeyDown(SDLK_p)) // Handle Pause
	{
		Game::Instance()->setState(Game::PAUSED);
		return;
	}
	
	Game::Instance()->getMngr()->update();
	Game::Instance()->getMngr()->refresh();

	checkCollisions();

	sdlutils().clearRenderer();
	Game::Instance()->getMngr()->render();
	sdlutils().presentRenderer();
}

void RunningState::checkCollisions() {

	// Transform
	auto tr = _mngr->getComponent<Transform>(fighter);

	// the GameCtrl component
	//auto ginfo = _mngr->getHandler(ecs::hdlr::GAMEINFO);
	//auto gctrl = _mngr->getComponent<GameCtrl>(ginfo);

	// For safety, we traverse with a normal loop until the current size.
	std::vector<ecs::entity_t> asteroids = _mngr->getEntities(ecs::grp::ASTEROIDS);
	int nAsteroids = asteroids.size();
	for (int i = 0; i < nAsteroids; ++i)
	{
		auto asEn = asteroids[i];
		if (_mngr->isAlive(asEn)) {
			auto asTr = _mngr->getComponent<Transform>(asEn);

			if ( Collisions::collides( tr->getPos(), tr->getWidth(), tr->getHeight(), asTr->getPos(), asTr->getWidth(), asTr->getHeight() ) ) {

				_mngr->setAlive(asEn, false);

				std::cout << "Asteroid hit player!" << std::endl;
				//gctrl->onStarEaten();

				// play sound on channel 1 (if there is something playing there
				// it will be cancelled
				//sdlutils().soundEffects().at("pacman_eat").play(0, 1);
			}
		}
	}
}
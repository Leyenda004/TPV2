#include "RunningState.h"

#include "Game.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Gun.h"
#include "../components/Health.h"
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
	int nAsteroids = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS).size();

	if(nAsteroids == 0 || _mngr->getComponent<Health>(fighter)->getLifeValue() <= 0)
	{
		Game::Instance()->setState(Game::GAMEOVER);
		return;
	}
	
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

	// For safety, we traverse with a normal loop until the current size.
	std::vector<ecs::entity_t> asteroids = _mngr->getEntities(ecs::grp::ASTEROIDS);

	int nAsteroids = asteroids.size();
	
	for (int i = 0; i < nAsteroids; ++i)
	{
		auto asteroidEnt = asteroids[i];

		if (_mngr->isAlive(asteroidEnt)) 
		{
			auto astTr = _mngr->getComponent<Transform>(asteroidEnt);

			if ( Collisions::collides( tr->getPos(), tr->getWidth(), tr->getHeight(), astTr->getPos(), astTr->getWidth(), astTr->getHeight() ) ) {

				_mngr->setAlive(asteroidEnt, false);

				std::cout << "Asteroid hit player!" << std::endl;
				_mngr->getComponent<Health>(fighter)->lifeUpdate(-1);

				if(_mngr->getComponent<Health>(fighter)->getLifeValue() > 0)
					Game::Instance()->setState(Game::NEWROUND);
				else
					Game::Instance()->setState(Game::GAMEOVER);
			}

			// Check collision with bullets
			Gun* gun = _mngr->getComponent<Gun>(fighter);

			Gun::iterator bulletIt = gun->begin();
			bool btCollision = false;

			while (bulletIt != gun->end() && !btCollision)
			{
				btCollision = Collisions::collides(
					astTr->getPos(), astTr->getWidth(), astTr->getHeight(),
					bulletIt->pos, bulletIt->width, bulletIt->height);

				++bulletIt;
			}

			if (bulletIt != gun->end())
			{
				bulletIt->used = false;
				Game::Instance()->asteroidsUtils()->split_astroid(asteroidEnt);
			}
				
		}
	}
}
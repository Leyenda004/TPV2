#include "RunningState.h"

#include "Game.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"

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
	
	if(ih().isKeyDown(SDL_Keycode::SDLK_p))
	{
		Game::Instance()->setState(Game::PauseState);
		return;
	}
	*/

	Game::Instance()->getMngr()->update();
	Game::Instance()->getMngr()->refresh();

	checkCollisions();

	sdlutils().clearRenderer();
	Game::Instance()->getMngr()->render();
	sdlutils().presentRenderer();
}

void RunningState::checkCollisions()
{
	ecs::entity_t fighter = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER);
	std::vector<ecs::entity_t> asteroids = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS);

	int nAsteroids = asteroids.size();

	for (int i = 0; i < nAsteroids; ++i)
	{
		
	}
}
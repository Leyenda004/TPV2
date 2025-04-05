#include "RunningState.h"

#include "Game.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "../sdlutils/InputHandler.h"

#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/StarsSystem.h"
#include "../systems/FoodSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/ImmunitySystem.h"

#include "../components/Transform.h"
#include "../components/Milagrosa.h"

#include <SDL.h>

RunningState::RunningState()
{
	_mngr = Game::Instance()->getMngr();

	_pacmanSys = _mngr->getSystem<PacManSystem>();
	_startsSys = _mngr->getSystem<StarsSystem>();
	_gameCtrlSys = _mngr->getSystem<GameCtrlSystem>();
	_renderSys = _mngr->getSystem<RenderSystem>();
	_collisionSys = _mngr->getSystem<CollisionsSystem>();
	_foodSys = _mngr->getSystem<FoodSystem>();
	_ghostSys = _mngr->getSystem<GhostSystem>();
	_immunitySys = _mngr->getSystem<ImmunitySystem>();
}

void RunningState::enter()
{

}

void RunningState::leave()
{

}

void RunningState::update()
{
	_pacmanSys->update();
	_startsSys->update();
	_gameCtrlSys->update();
	_collisionSys->update();
	_foodSys->update();
	_ghostSys->update();
	_immunitySys->update();

	_mngr->refresh();

	checkCollisions();

	sdlutils().clearRenderer();
	_renderSys->update();
	sdlutils().presentRenderer();
}

void RunningState::checkCollisions()
{
	auto pacman = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto pacmanTr = _mngr->getComponent<Transform>(pacman);

	auto foods = _mngr->getEntities(ecs::grp::FOOD);
	for (int i = 0; i < foods.size(); i++) {
		auto food = foods[i];
		auto foodTr = _mngr->getComponent<Transform>(food);

		if (Collisions::collides(
			pacmanTr->_pos, pacmanTr->_width, pacmanTr->_height,
			foodTr->_pos, foodTr->_width, foodTr->_height)) 
			{
				_mngr->setAlive(food, false);

				if (_mngr->getComponent<Milagrosa>(food)->fruitChanged) {
					// mandar mensaje !!
				}
			}
	}
}

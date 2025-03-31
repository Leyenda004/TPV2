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

	_mngr->refresh();

	sdlutils().clearRenderer();
	_renderSys->update();
	sdlutils().presentRenderer();
}

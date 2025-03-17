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
}

void RunningState::enter()
{

}

void RunningState::leave()
{

}

void RunningState::update()
{
	
}

void RunningState::checkCollisions() {


}
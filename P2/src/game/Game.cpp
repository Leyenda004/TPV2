// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/StarsSystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

// PRACTICA
#include "../game/RunningState.h"
#include "../game/PausedState.h"
#include "../game/GameOverState.h"

#include "../systems/FoodSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/ImmunitySystem.h"

using ecs::Manager;

Game::Game() :
		_mngr(), //
		_pacmanSys(), //
		_gameCtrlSys(), //
		_startsSys(), //
		_renderSys(), //
		_collisionSys()//,
//		_ghostSys()
{

}

Game::~Game() {
	delete _mngr;

	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();
}

bool Game::init() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("PacMan, Stars, ...", 800, 600,
			"resources/config/resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return false;
	}

	// initialize the InputHandler singleton
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing SDLHandler"
				<< std::endl;
		return false;

	}

	// Create the manager
	_mngr = new Manager();

	// add the systems
	_mngr->addSystem<PacManSystem>();
	//_mngr->addSystem<StarsSystem>();
	//_mngr->addSystem<GameCtrlSystem>();
	_mngr->addSystem<RenderSystem>();
	_mngr->addSystem<CollisionsSystem>();
	
	// PRACTICA

	_mngr->addSystem<FoodSystem>();
	_mngr->addSystem<GhostSystem>();
	_mngr->addSystem<ImmunitySystem>();

	// Game States
	_running_state = new RunningState();
	_paused_state = new PausedState();
	_gameovergood_state = new GameOverState(1);
	_gameoverbad_state = new GameOverState(0);

	_state = _running_state;

	return true;
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		// Uint32 startTime = sdlutils().virtualTimer().currTime();
		Uint32 startTime = sdlutils().virtualTimer().regCurrTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		_state->update();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}


// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

// PRACTICA
#include "NewGameState.h"
#include "NewRoundState.h"
#include "RunningState.h"
#include "PausedState.h"
#include "GameOverState.h"

using ecs::Manager;

Game::Game() :
		_mngr(nullptr) {
	
}

Game::~Game() {

	if(_paused_state != nullptr)   delete _paused_state;
	if(_running_state != nullptr)  delete _running_state;
	if(_newgame_state != nullptr)  delete _newgame_state;
	if(_newround_state != nullptr) delete _newround_state;
	if(_gameover_state != nullptr) delete _gameover_state;

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
	if (!SDLUtils::Init("STAR FIGHTER", 800, 600,
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

	return true;
}

void Game::initGame()
{
	fu = new FighterUtils();
	fu->create_fighter();

	asteroidUtils = new AsteroidsUtils();
	asteroidUtils->create_asteroids(10);

	_paused_state = new PausedSate();
	_running_state = new RunningState();
	_newgame_state = new NewGameState();
	_newround_state = new NewRoundState();
	_gameover_state = new GameOverState();

	_state = _newgame_state;
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	// reset the time before starting - so we calculate correct
	// delta-time in the first iteration
	//
	auto& vt = sdlutils().virtualTimer();
	vt.resetTime();

	while (!exit) {
		// store the current time -- all game objects should use this time when
		// then need to the current time. They also have accessed to the time elapsed
		// between the last two calls to regCurrTime().
		Uint32 startTime = sdlutils().regCurrTime();

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

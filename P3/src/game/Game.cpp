// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "LittleWolf.h"
#include "Networking.h"

Game::Game() :
		_little_wolf() //
		//net_(nullptr)
{
}

Game::~Game() {

	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();

	delete _little_wolf;
}

bool Game::init() {
	return true;
}

bool Game::initGame(char* host, Uint16 port, const char *map) {
	
	
	net_ = new Networking();

	if (!net_->init(host, port)) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}
	std::cout << "Connected as client " << (int) net_->client_id() << std::endl;
	
	
	_little_wolf = new LittleWolf();

	// load a map
	_little_wolf->load(map);

	// initialize the SDL singleton
	if (!SDLUtils::Init("[Little Wolf: " + std::string(map) + "]",
			_little_wolf->get_xres(),
			_little_wolf->get_yres(),
			"resources/config/littlewolf.resources.json")) {

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

	_little_wolf->init(sdlutils().window(), sdlutils().renderer());
	
	// add player
	_little_wolf->addPlayer(net_->client_id());
	
	return true;
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.keyDownEvent()) {

			// ESC exists the game
			if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
				exit = true;
				continue;
			}

		}

		_little_wolf->update();
		net_->update(); // Handles the messages that the client could have reicived

		// the clear is not necessary since the texture we copy to the window occupies the whole screen
		// sdlutils().clearRenderer();

		_little_wolf->render();

		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

	net_->disconnect();
}


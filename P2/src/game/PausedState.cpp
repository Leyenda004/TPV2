#include "PausedState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"

PausedState::PausedState()
{
	_continueMessage = new Texture(sdlutils().renderer(), "press any key to resume the game",
		sdlutils().fonts().at("ARIAL24"), SDL_Color{255, 255, 255, 255}, SDL_Color{ 127, 127, 127, 230 });
}

void PausedState::enter()
{
	sdlutils().virtualTimer().pause();
}

void PausedState::leave()
{
	sdlutils().virtualTimer().resume();
}

void PausedState::update()
{
	sdlutils().clearRenderer();

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {
		Game::Instance()->setState(Game::RUNNING);
		return;
	}

	int x = sdlutils().width() / 2 - _continueMessage->width() / 2;
	int y = sdlutils().height() / 2 - _continueMessage->height() / 2;
	_continueMessage->render(x, y);
	
	sdlutils().presentRenderer();
}
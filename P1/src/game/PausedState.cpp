#include "PausedState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"

PausedSate::PausedSate()
{
	_continueMessage = new Texture(sdlutils().renderer(), "press any key to resume the game",
		sdlutils().fonts().at("ARIAL24"), SDL_Color{255, 255, 255, 255}, SDL_Color{ 127, 127, 127, 230 });
}

void PausedSate::enter()
{
	sdlutils().virtualTimer().pause();
}

void PausedSate::leave()
{
	sdlutils().virtualTimer().resume();
}

void PausedSate::update()
{
	sdlutils().clearRenderer();

	if (ih().keyDownEvent()) {
		Game::Instance()->setState(Game::RUNNING);
		return;
	}

	int x = sdlutils().width() / 2 - _continueMessage->width() / 2;
	int y = sdlutils().height() / 2 - _continueMessage->height() / 2;
	_continueMessage->render(x, y);
	
	sdlutils().presentRenderer();
}
#include "NewGameState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"

NewGameState::NewGameState()
{
	_startMessage = new Texture(sdlutils().renderer(), "press any key to start a new game",
		sdlutils().fonts().at("ARIAL24"), SDL_Color{ 255, 255, 255, 255 }, SDL_Color{ 127, 127, 127, 230 });
}

void NewGameState::enter()
{
	
}

void NewGameState::leave()
{
	
}

void NewGameState::update()
{
	sdlutils().clearRenderer();

	if (ih().keyDownEvent()) {
		Game::Instance()->setState(Game::RUNNING); // TODO Change state
		return;
	}

	int x = sdlutils().width() / 2 - _startMessage->width() / 2;
	int y = sdlutils().height() / 2 - _startMessage->height() / 2;
	_startMessage->render(x, y);

	sdlutils().presentRenderer();
}
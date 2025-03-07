#include "NewRoundState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"

NewRoundState::NewRoundState()
{
	_startMessage = new Texture(sdlutils().renderer(), "press ENTER to start the round",
		sdlutils().fonts().at("ARIAL24"), SDL_Color{ 255, 255, 255, 255 }, SDL_Color{ 127, 127, 127, 230 });
}

void NewRoundState::enter()
{

}

void NewRoundState::leave()
{

}

void NewRoundState::update()
{
	sdlutils().clearRenderer();

	if (ih().keyDownEvent() && ih().isKeyDown(SDLK_KP_ENTER))
	{
		Game::Instance()->fighterUtils()->reset_fighter();
		Game::Instance()->asteroidsUtils()->remove_all_asteroids();
		Game::Instance()->asteroidsUtils()->create_asteroids(10);

		Game::Instance()->setState(Game::RUNNING);
		return;
	}

	int x = sdlutils().width() / 2 - _startMessage->width() / 2;
	int y = sdlutils().height() / 2 - _startMessage->height() / 2;
	_startMessage->render(x, y);

	sdlutils().presentRenderer();
}
#include "GameOverState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"

GameOverState::GameOverState()
{
	
}

void GameOverState::enter()
{

}

void GameOverState::leave()
{

}

void GameOverState::update()
{
	sdlutils().clearRenderer();

	if (ih().isKeyDown(SDLK_RETURN))
	{

		Game::Instance()->setState(Game::NEWGAME);
		return;
	}

	int x = sdlutils().width() / 2 - _gameOverMessage->width() / 2;
	int y = sdlutils().height() / 2 - _gameOverMessage->height() / 2;
	_gameOverMessage->render(x, y);

	sdlutils().presentRenderer();
}
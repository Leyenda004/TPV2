#include "GameOverState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"

GameOverState::GameOverState(int n) // 0 you lost, 1 you won
{
	if (n == 0)
		_gameOverMessage = new Texture(sdlutils().renderer(), "Game Over. You Lost", sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xFF0000FF));
	else
		_gameOverMessage = new Texture(sdlutils().renderer(), "Game Over. You Won", sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0x00FF00FF));
	
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
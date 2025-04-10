#include "GameOverState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"
#include "../ecs/Manager.h"
#include "../systems/GameCtrlSystem.h"

GameOverState::GameOverState()
{
	
}

void GameOverState::enter()
{
	if (Game::Instance()->getMngr()->getSystem<GameCtrlSystem>()->gameOverWin())
		_gameOverMessage = new Texture(sdlutils().renderer(), "Game Over Champion! Press ENTER to continue.", sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x00FF00FF));
	else
		_gameOverMessage = new Texture(sdlutils().renderer(), "Game Over Loser! Press ENTER to continue.", sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0xFF0000FF));

}

void GameOverState::leave()
{

}

void GameOverState::update()
{
	sdlutils().clearRenderer();

	if (ih().keyDownEvent())
	{

		Game::Instance()->setState(Game::NEWGAME);
		return;
	}

	int x = sdlutils().width() / 2 - _gameOverMessage->width() / 2;
	int y = sdlutils().height() / 2 - _gameOverMessage->height() / 2;
	_gameOverMessage->render(x, y);

	sdlutils().presentRenderer();
}
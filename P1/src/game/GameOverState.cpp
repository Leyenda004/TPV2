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
	bool playerWon = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS).size() == 0;

	std::string playerState = playerWon? "Champion" : "Loser";

	_gameOverMessage = new Texture(sdlutils().renderer(), "Game Over " + playerState + "! Press ENTER to continue.",
		sdlutils().fonts().at("ARIAL24"), SDL_Color{ 255, 255, 255, 255 }, SDL_Color{ 127, 127, 127, 230 });
}

void GameOverState::leave()
{

}

void GameOverState::update()
{
	sdlutils().clearRenderer();

	if (ih().isKeyDown(SDLK_RETURN))
	{
		Game::Instance()->fighterUtils()->reset_fighter();
		Game::Instance()->asteroidsUtils()->remove_all_asteroids();
		Game::Instance()->asteroidsUtils()->create_asteroids(10);

		Game::Instance()->setState(Game::NEWGAME);
		return;
	}

	int x = sdlutils().width() / 2 - _gameOverMessage->width() / 2;
	int y = sdlutils().height() / 2 - _gameOverMessage->height() / 2;
	_gameOverMessage->render(x, y);

	sdlutils().presentRenderer();
}
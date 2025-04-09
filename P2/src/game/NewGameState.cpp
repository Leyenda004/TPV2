#include "NewGameState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"
#include "../ecs/Manager.h"
#include "../systems/FoodSystem.h"
#include "../game/messages_defs.h"

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

	if (ih().keyDownEvent()) 
	{
		Game::Instance()->getMngr()->getSystem<FoodSystem>()->reset();
		Game::Instance()->getMngr()->getSystem<FoodSystem>()->spawnFood();

		Message m;
		m.id = _m_NEW_GAME;
		Game::Instance()->getMngr()->send(m);

		Game::Instance()->setState(Game::NEWROUND);
		
		return;
	}

	int x = sdlutils().width() / 2 - _startMessage->width() / 2;
	int y = sdlutils().height() / 2 - _startMessage->height() / 2;
	_startMessage->render(x, y);

	sdlutils().presentRenderer();
}
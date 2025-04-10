#include "NewRoundState.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"
#include "../game/messages_defs.h"
#include "../ecs/Manager.h"
#include "../systems/PacManSystem.h"
#include "../systems/GhostSystem.h"

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

	if (ih().keyDownEvent() && ih().isKeyDown(SDLK_RETURN))
	{
		Message m;
		m.id = _m_ROUND_START;
		Game::Instance()->getMngr()->send(m);

		Game::Instance()->setState(Game::RUNNING);

		return;
	}

	int x = sdlutils().width() / 2 - _startMessage->width() / 2;
	int y = sdlutils().height() / 2 - _startMessage->height() / 2;
	_startMessage->render(x, y);

	sdlutils().presentRenderer();
}
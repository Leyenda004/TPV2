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


}
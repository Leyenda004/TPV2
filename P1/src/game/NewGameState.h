#pragma once
#include "GameState.h"

class Texture;

class NewGameState : public GameState
{
public:
	NewGameState();
	~NewGameState() {}

	void enter() override;
	void leave() override;
	void update() override;

protected:

	Texture* _startMessage;
};
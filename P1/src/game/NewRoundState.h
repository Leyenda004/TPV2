#pragma once
#include "GameState.h"

class Texture;

class NewRoundState : public GameState
{
public:
	NewRoundState();
	~NewRoundState() {}

	void enter() override;
	void leave() override;
	void update() override;

protected:

	Texture* _startMessage;
};
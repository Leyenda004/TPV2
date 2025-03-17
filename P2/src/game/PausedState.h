#pragma once
#include "GameState.h"

class Texture;

class PausedSate : public GameState
{
public:

	PausedSate();
	~PausedSate() {}

	void enter() override;
	void leave() override;
	void update() override;

protected:

	Texture* _continueMessage;
};
#pragma once
#include "GameState.h"
class RunningState : public GameState
{
	RunningState(){}
	~RunningState(){}

	void enter() override;
	void leave() override;
	void update() override;

protected:

	void checkCollisions();
};


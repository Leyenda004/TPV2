#pragma once
#include "GameState.h"
#include "../ecs/ecs.h"

namespace ecs {
	class Manager;
}

class RunningState : public GameState
{
public:

	RunningState();
	~RunningState(){}

	void enter() override;
	void leave() override;
	void update() override;

protected:

	void checkCollisions();

	ecs::entity_t fighter;
	ecs::Manager* _mngr;
};
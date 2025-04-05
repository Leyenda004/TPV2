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

	ecs::System* _pacmanSys;
	ecs::System* _gameCtrlSys;
	ecs::System* _startsSys;
	ecs::System* _renderSys;
	ecs::System* _collisionSys;
	ecs::System* _foodSys;
	ecs::System* _ghostSys;
	ecs::System* _immunitySys;

	ecs::Manager* _mngr;
};
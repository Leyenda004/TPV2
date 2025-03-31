// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

#include "../ecs/ecs.h"
#include "../utils/Singleton.h"
#include "GameState.h"

class Game : public Singleton<Game>
{
public:
	
	bool init();
	void start();

	ecs::Manager* getMngr() { return _mngr; }

	enum State {
		RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER
	};

	inline void setState(State s) {
		_state->leave();
		switch (s) {
		case RUNNING:
			_state = _running_state;
			break;
		case PAUSED:
			_state = _paused_state;
			break;
		case NEWGAME:
			_state = _newgame_state;
			break;
		case NEWROUND:
			_state = _newround_state;
			break;
		case GAMEOVER:
			_state = _gameover_state;
			break;
		default:
			break;
		}
		_state->enter();
	}

private:

	friend Singleton<Game>;
	
	Game();
	virtual ~Game();

	ecs::Manager *_mngr;

	ecs::System *_pacmanSys;
	ecs::System *_gameCtrlSys;
	ecs::System *_startsSys;
	ecs::System *_renderSys;
	ecs::System *_collisionSys;
	ecs::System *_foodSys;
	ecs::System *_ghostSys;

	GameState* _state;
	GameState* _paused_state;
	GameState* _running_state;
	GameState* _newgame_state;
	GameState* _newround_state;
	GameState* _gameover_state;
};


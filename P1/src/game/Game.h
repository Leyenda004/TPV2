// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../utils/Singleton.h"

namespace ecs {
class Manager;
}

class Game : public Singleton<Game>
{
public:

	bool init();
	void initGame();
	void start();
	ecs::Manager* getMngr() { return _mngr; }

private:

	friend Singleton<Game>;

	Game();
	virtual ~Game();

	void checkCollisions();
	ecs::Manager *_mngr;
};


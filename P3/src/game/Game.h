// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../utils/Singleton.h"

class Networking;
class LittleWolf;

class Game : public Singleton<Game> {

	friend Singleton<Game>;

public:
	
	void initGame(const char *map);
	void start();

	Networking& get_networking() {
		return *net_;
	}

private:
	
	Game();
	virtual ~Game();

	bool init();
	
	LittleWolf *_little_wolf;
	Networking* net_;
};


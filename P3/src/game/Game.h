// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../utils/Singleton.h"
#include <SDL.h>

class Networking;
class LittleWolf;

class Game : public Singleton<Game> {

	friend Singleton<Game>;

public:
	
	bool initGame(char* host, Uint16 port, const char *map);
	void start();

	Networking& get_networking() {
		return *net_;
	}

	LittleWolf& get_little_wolf() {
		return *_little_wolf;
	}

private:
	
	Game();
	virtual ~Game();

	bool init();
	
	LittleWolf *_little_wolf;
	Networking* net_;
};


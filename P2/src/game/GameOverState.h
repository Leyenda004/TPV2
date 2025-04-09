#pragma once
#include "GameState.h"

class Texture;

class GameOverState : public GameState
{
public:
	GameOverState(int);
	~GameOverState() {}

	void enter() override;
	void leave() override;
	void update() override;

protected:

	Texture* _gameOverMessage = nullptr;
};
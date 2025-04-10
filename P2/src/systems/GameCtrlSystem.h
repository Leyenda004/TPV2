// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class GameCtrlSystem: public ecs::System {
public:

	GameCtrlSystem();
	virtual ~GameCtrlSystem();

	void initSystem() override;
	void update() override;
	void recieve(const Message &m) override;

	bool gameOverWin() {
		return _gameOverWin;
	}

private:
	
	bool _gameOverWin = true;
};


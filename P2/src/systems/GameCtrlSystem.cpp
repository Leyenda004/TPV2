// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"

#include "../components/Points.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "StarsSystem.h"
GameCtrlSystem::GameCtrlSystem() :
		_score() {
	// TODO Auto-generated constructor stub

}

GameCtrlSystem::~GameCtrlSystem() {
	// TODO Auto-generated destructor stub
}

void GameCtrlSystem::initSystem() {
}

void GameCtrlSystem::update() {
	
}

void GameCtrlSystem::recieve(const Message &m) {
	switch (m.id) {
	 case _m_GAME_OVER:
		 _gameOverWin = m.game_over_data.playerWon;
	 	break;
	default:
		break;
	}
}

// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class CollisionsSystem: public ecs::System {
public:

	CollisionsSystem();
	virtual ~CollisionsSystem();
	void initSystem() override;
	void update() override;

	void checkCollisionInFruits();
	void checkCollisionGhostPacman();
};


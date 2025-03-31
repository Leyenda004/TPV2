#pragma once
#include "../ecs/System.h"
#include "../utils/Vector2D.h"

#include <SDL.h>

class GhostSystem : public ecs::System
{
public:

	GhostSystem(){}
	virtual ~GhostSystem() {}

	void initSystem() override;
	void update() override;

	void startGeneration();
	Vector2D getRandomCornerPosition();
	
private:

	Uint32 initTime;
	int generationWaitTime = 5;
	int ghostsNum = 0;
	int maxGhosts = 10;
};
#pragma once
#include "../ecs/System.h"

#include <SDL.h>

class GhostSystem : public ecs::System
{
public:

	GhostSystem(){}
	virtual ~GhostSystem() {}

	void initSystem() override;
	void update() override;

	void startGeneration();
	
private:

	Uint32 initTime;
	int generationWaitTime;
	int ghostsNum = 0;
};
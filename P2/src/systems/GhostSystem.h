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
	void recieve(const Message&) override;

	void startGeneration();

protected:

	void reset();
	void createGhost();
	
private:
	void onPlayerCollides(ecs::entity_t e);

	Transform* pmTr;
	float ghostSize;

	Uint32 lastInstanceTime;
	int generationWaitTime = 5000;
	int maxGhosts = 10;
};
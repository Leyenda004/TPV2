#pragma once
#include "../ecs/System.h"

class FoodSystem : public ecs::System
{
public:

	FoodSystem() {};
	virtual ~FoodSystem() {};
	void initSystem() override;
	void update() override;

private:
	void spawnFood();
};


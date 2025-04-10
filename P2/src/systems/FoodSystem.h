#pragma once
#include "../ecs/System.h"

class FoodSystem : public ecs::System
{
public:

	FoodSystem() {};
	virtual ~FoodSystem() {};
	void initSystem() override;
	void update() override;

	void recieve(const Message&) override;

	void onFoodEaten(ecs::entity_t e);

private:

	void spawnFood();
	void reset();

	int _aliveFruits;
};


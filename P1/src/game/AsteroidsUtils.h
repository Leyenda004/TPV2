#pragma once 
#include "AsteroidsFacade.h"

class AsteroidsUtils : public AsteroidsFacade
{
public:
	AsteroidsUtils();

	void create_asteroids(int n) override;
	void remove_all_asteroids() override;
	void split_astroid(ecs::Entity* a) override;
};
#pragma once
#include "../ecs/System.h"

#include <SDL.h>

class ImmunitySystem : public ecs::System
{
public:

	ImmunitySystem(){}
	virtual ~ImmunitySystem(){}

	void initSystem() override;
	void update() override;

	void recieve(const Message&) override;

	bool pacmanIsImmune() { return _pacmanIsImmune; }

private:

	bool _pacmanIsImmune = false;
	Uint32 _immunityInnitTime;
	Uint32 _immunityDurationTime = 10000;
};
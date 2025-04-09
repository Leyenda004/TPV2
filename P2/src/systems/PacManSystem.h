// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"

struct Transform;
struct Health;
struct ImageWithFrames;

class PacManSystem: public ecs::System {
public:

	PacManSystem();
	virtual ~PacManSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& m) override;

	void reset();
private:

	void onGhostCollides();

	Transform *_pmTR;
	Health* health;
	ImageWithFrames* sprite;
};


// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

#include <SDL.h>

class Texture;
struct Transform;

class RenderSystem: public ecs::System {
public:

	RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;

private:

	void drawPacMan();
	void drawFood();
	void drawGhosts();
	void drawLives();
	void draw(Transform *tr, Texture *tex);

	Uint32 ghostFrameTime;
	Uint32 pacmanFrameTime;
};


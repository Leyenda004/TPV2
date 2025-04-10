// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

#include "GameCtrlSystem.h"
#include "ImmunitySystem.h"

RenderSystem::RenderSystem() 
{
	ghostFrameTime = sdlutils().virtualTimer().currTime();
	pacmanFrameTime = sdlutils().virtualTimer().currTime();
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	//drawMsgs();
	//drawStars();
	drawFood();
	drawPacMan();
	drawGhosts();
	drawLives();
}

void RenderSystem::drawFood() {
	for (auto e : _mngr->getEntities(ecs::grp::FOOD)) {

		auto tr = _mngr->getComponent<Transform>(e);
		//auto tex = _mngr->getComponent<Image>(e)->_tex;
		auto iWFs = _mngr->getComponent<ImageWithFrames>(e);
		auto tex = iWFs->_tex;

		SDL_Rect dest = build_sdlrect(tr->_pos, tr->_width, tr->_height);
		
		int frameW = iWFs->_tex->width() / iWFs->_cols;
		int frameH = iWFs->_tex->height() / iWFs->_rows;
		
		SDL_Rect src = { (int)(iWFs->getFrame() % iWFs->_cols) * frameH, (int)(iWFs->getFrame() / iWFs->_rows) * frameW, frameH, frameW};
		//SDL_Rect src = { 4, 1, frameW, frameH};
		tex->render(src, dest);
		//if (tex != nullptr) draw(tr, tex);
	}
}

void RenderSystem::drawPacMan() {
	auto e = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto tr = _mngr->getComponent<Transform>(e);

	
	auto iWFs = _mngr->getComponent<ImageWithFrames>(e);
	auto tex = iWFs->_tex;

	SDL_Rect dest = build_sdlrect(tr->_pos, tr->_width, tr->_height);
	
	int frameW = iWFs->_tex->width() / iWFs->_cols;
	int frameH = iWFs->_tex->height() / iWFs->_rows;

	if (sdlutils().virtualTimer().currTime() - pacmanFrameTime > 100)
	{
		++iWFs->_frame;
		pacmanFrameTime = sdlutils().virtualTimer().currTime();
	}

	iWFs->_frame = iWFs->_frame % 2;
	
	SDL_Rect src = { (int)(iWFs->getFrame() % iWFs->_cols) * frameH, (int)(iWFs->getFrame() / iWFs->_rows) * frameW, frameH, frameW};
	tex->render(src, dest, tr->_rot);
}

void RenderSystem::draw(Transform *tr, Texture *tex) {
	SDL_Rect dest = build_sdlrect(tr->_pos, tr->_width, tr->_height);

	assert(tex != nullptr);
	tex->render(dest, tr->_rot);
}

void RenderSystem::drawGhosts()
{
	auto pm = _mngr->getHandler(ecs::hdlr::PACMAN);
	ImmunitySystem* pmImmunity = _mngr->getSystem<ImmunitySystem>();

	for (auto e : _mngr->getEntities(ecs::grp::GHOSTS)) 
	{
		auto tr = _mngr->getComponent<Transform>(e);
		auto iWFs = _mngr->getComponent<ImageWithFrames>(e);
		auto tex = iWFs->_tex;

		SDL_Rect dest = build_sdlrect(tr->_pos, tr->_width, tr->_height);

		int frameW = iWFs->_tex->width() / iWFs->_cols;
		int frameH = iWFs->_tex->height() / iWFs->_rows;

		int frameSet = 32;
		if(pmImmunity->pacmanIsImmune()) frameSet = 48;

		if (sdlutils().virtualTimer().currTime() - ghostFrameTime > 500)
		{
			++iWFs->_frame;
			ghostFrameTime = sdlutils().virtualTimer().currTime();
		}
			
		
		iWFs->_frame = (iWFs->_frame % 8) + frameSet;

		SDL_Rect src = { (int)(iWFs->getFrame() % iWFs->_cols) * frameH, (int)(iWFs->getFrame() / iWFs->_rows) * frameW, frameH, frameW };

		tex->render(src, dest);
	}
}

void RenderSystem::drawLives()
{
	auto lives = _mngr->getComponent<Health>(_mngr->getHandler(ecs::hdlr::PACMAN));
	for (int i = 0; i < lives->vida; ++i)
	{
		auto tex = &sdlutils().images().at("heart");
		Vector2D pos = Vector2D(10 + i * (tex->width()/4 + 10), 10);
		SDL_Rect dest = build_sdlrect(pos, tex->width()/4, tex->height()/4);
		tex->render(dest);
	}
}
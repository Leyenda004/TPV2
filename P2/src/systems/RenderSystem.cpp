// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawMsgs();
	//drawStars();
	drawFood(); // !!
	drawPacMan();
}

void RenderSystem::drawStars() {
	// draw stars
	for (auto e : _mngr->getEntities(ecs::grp::STARS)) {

		auto tr = _mngr->getComponent<Transform>(e);
		auto tex = _mngr->getComponent<Image>(e)->_tex;
		draw(tr, tex);
	}
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
	auto tex = _mngr->getComponent<Image>(e)->_tex;
	draw(tr, tex);

}


void RenderSystem::drawMsgs() {
	// draw the score
	//
	auto score = _mngr->getSystem<GameCtrlSystem>()->getScore();

	Texture scoreTex(sdlutils().renderer(), std::to_string(score),
			sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x444444ff));

	SDL_Rect dest = build_sdlrect( //
			(sdlutils().width() - scoreTex.width()) / 2.0f, //
			10.0f, //
			scoreTex.width(), //
			scoreTex.height());

	scoreTex.render(dest);

	// draw add stars message
	sdlutils().msgs().at("addstars").render(10, 10);

}

void RenderSystem::draw(Transform *tr, Texture *tex) {
	SDL_Rect dest = build_sdlrect(tr->_pos, tr->_width, tr->_height);

	assert(tex != nullptr);
	tex->render(dest, tr->_rot);
}

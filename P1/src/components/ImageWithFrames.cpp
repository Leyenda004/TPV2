#include "ImageWithFrames.h"


#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"

ImageWithFrames::ImageWithFrames() : _tr(), _tex(&sdlutils().images().at("asteroids")), frame(0), nFrames(30)
{
}

ImageWithFrames::ImageWithFrames(Texture* tex) : _tr(), _tex(tex), frame(0), nFrames(0)
{
}

void ImageWithFrames::initComponent()
{
	auto* mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
	_frameInitTime = sdlutils().virtualTimer().currTime();
}

void ImageWithFrames::update()
{
	if (sdlutils().virtualTimer().currTime() % 500 == 0) 
	{
		_frameInitTime = sdlutils().virtualTimer().currTime();
		++frame;
		if (frame > nFrames) frame = 0;
	}
}

void ImageWithFrames::render()
{
	SDL_Rect dest = build_sdlrect(_tr->getPos(), _tr->getWidth(),
		_tr->getHeight());

	int frameW = _tex->width() / 6;
	int frameH = _tex->height() / 5;

	SDL_Rect src = { (int)(frame % 6) * frameW, (int)(frame / 5) * frameH, frameW, frameH };

	assert(_tex != nullptr);
	_tex->render(src, dest);
}
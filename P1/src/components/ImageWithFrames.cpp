#include "ImageWithFrames.h"


#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"

ImageWithFrames::ImageWithFrames(Texture* tex, int frames, int rows, int cols) 
	: _tr(), _tex(tex), _frame(0), _nFrames(frames), _rows(rows), _cols(cols)
{
}

void ImageWithFrames::initComponent()
{
	auto* mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
	
	_frameInitTime = sdlutils().virtualTimer().currRealTime();
}

void ImageWithFrames::update()
{
	if (sdlutils().virtualTimer().currRealTime() - _frameInitTime >= 50)
	{
		_frameInitTime = sdlutils().virtualTimer().currRealTime();
		++_frame;
		if (_frame >= _nFrames) _frame = 0;
	}
}

void ImageWithFrames::render()
{
	SDL_Rect dest = build_sdlrect(_tr->getPos(), _tr->getWidth(),
		_tr->getHeight());

	int frameW = _tex->width() / _cols;
	int frameH = _tex->height() / _rows;

	SDL_Rect src = { (int)(_frame / _cols) * frameW, (int)(_frame % _rows) * frameH, frameW, frameH };

	assert(_tex != nullptr);
	_tex->render(src, dest);
}
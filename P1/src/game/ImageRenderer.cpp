// This file is part of the course TPV2@UCM - Samir Genaim

#include "ImageRenderer.h"

#include "../sdlutils/Texture.h"
#include "Container.h"

ImageRenderer::ImageRenderer(Texture *img) :
		_img(img) {
}

ImageRenderer::~ImageRenderer() {
}

void ImageRenderer::render(Container* o) {
	SDL_Rect dest = build_sdlrect(o->getPos(), o->getWidth(), o->getHeight());
	_img->render(dest, o->getRotation());
}

// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "RenderComponent.h"

class Texture;

class ImageRenderer: public RenderComponent {
public:
	ImageRenderer(Texture *img);
	virtual ~ImageRenderer();
	void render(Container *o) override;
	// duda, si float r fuese opcional (se pusiese uno predeterminado), que metodo se ejecutaria
	/*void render(Container *o, float r);*/
private:
	Texture *_img;
};


#pragma once
#include "../ecs/Component.h"
#include <SDL.h>

class Transform;
class Texture;

class ImageWithFrames : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::IMAGE_WITH_FRAMES)

	ImageWithFrames(Texture* tex, int frames, int rows, int cols);
	virtual ~ImageWithFrames(){}

	void setTexture(Texture* tex) {
		_tex = tex;
	}

	void initComponent() override;
	void update() override;
	void render() override;

private:

	Transform* _tr;
	Texture* _tex;

	Uint32 _frameInitTime;
	int _frame;
	int _nFrames;
	int _rows;
	int _cols;
};
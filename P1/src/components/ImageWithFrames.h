#pragma once
#include "../ecs/Component.h"
#include <SDL.h>

class Transform;
class Texture;

class ImageWithFrames : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::IMAGE_WITH_FRAMES)

	ImageWithFrames();
	ImageWithFrames(Texture* tex);
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
	int frame;
	int nFrames;
};
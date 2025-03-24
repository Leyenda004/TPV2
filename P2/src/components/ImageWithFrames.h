#pragma once
#include "../ecs/Component.h"
#include <SDL.h>

class Transform;
class Texture;

struct ImageWithFrames : public ecs::Component {

	ImageWithFrames(Texture* tex, int frames, int rows, int cols) : 
		_tr(), _tex(tex), _nFrames(frames), _rows(rows), _cols(cols) {}
	virtual ~ImageWithFrames() {}

	//void initComponent();

	int getFrame() { return _frame; }
	void setFrame(int frame) { _frame = frame; }

	Transform* _tr;
	Texture* _tex;

	Uint32 _frameInitTime;
	int _frame;
	int _nFrames;
	int _rows;
	int _cols;
};


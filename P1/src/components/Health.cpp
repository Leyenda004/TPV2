#include "Health.h"

Health::Health(int lifeMax = 3) : _lifeMax(lifeMax), _lifeNum(lifeMax) {}

Health::Health() : Health(3) {}

void Health::initComponent() {

	_healthTex = &sdlutils().images().at("heart");
}

void Health::render() {
	for (int i = 0; i < _lifeNum; i++) {
		SDL_Rect dest = build_sdlrect(25 + i * 75, 25, 50, 50);
		_healthTex->render(dest);
	}
}
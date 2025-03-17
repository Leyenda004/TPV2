#include "FoodSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
//#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

void FoodSystem::initSystem()
{
	spawnFood();
}

void FoodSystem::update() {
	auto currTime = sdlutils().currRealTime();
	auto foods = _mngr->getEntities(ecs::grp::FOOD);
	auto n = foods.size();
}

void FoodSystem::spawnFood() {

	int spaceBetweenX = sdlutils().width() / 8; //px
	int spaceBetweenY = sdlutils().height() / 6; //px
	int s = 50; //px

	for (int i = 0; i < 8; i++) { //modificar a tamano de array
		auto x = (s / 2) + spaceBetweenX * i;
		for (int j = 0; j < 6; j++) {
			// add and entity to the manager
			//
			auto e = _mngr->addEntity(ecs::grp::FOOD);

			// add a Transform component, and initialise it with random
			// size and position
			//
			auto tr = _mngr->addComponent<Transform>(e);
			auto y = (s / 2) + spaceBetweenY * j;
			tr->init(Vector2D(x, y), Vector2D(0, 0), s, s, 0.0f);

			std::cout << x << " " << y << std::endl;

			// add an Image Component
			//
			_mngr->addComponent<Image>(e, &sdlutils().images().at("star"));
		}

	}
}
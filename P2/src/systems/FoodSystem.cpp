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

	int spaceBetween = 50; //px
	int s = 50; //px

	for (int i = 1; i < 49; i++) { //modificar a tamano de array

		// add and entity to the manager
		//
		auto e = _mngr->addEntity(ecs::grp::FOOD);

		// add a Transform component, and initialise it with random
		// size and position
		//
		auto tr = _mngr->addComponent<Transform>(e);
		auto x = i * (spaceBetween + s / 2) % 8;
		auto y = i * (spaceBetween + s / 2) / 6;
		tr->init(Vector2D(x, y), Vector2D(0, 0), s, s, 0.0f);

		std::cout << x << " " << y << std::endl;

		// add an Image Component
		//
		_mngr->addComponent<Image>(e, &sdlutils().images().at("star"));

	}
}
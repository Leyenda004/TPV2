#include "FoodSystem.h"

#include <random>

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
//#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../components/ImageWithFrames.h"
#include "../components/Milagrosa.h"

void FoodSystem::initSystem()
{
	spawnFood();
}

void FoodSystem::update() {
	auto currTime = sdlutils().virtualTimer().currTime();
	auto foods = _mngr->getEntities(ecs::grp::FOOD);
	//auto n = foods.size();

	for (auto e : foods) {
		auto milagrosa = _mngr->getComponent<Milagrosa>(e);
		if (milagrosa->milagrosa){
			std::cout << "N: " << milagrosa->N << " M: " << milagrosa->M << std::endl;
			if (currTime > milagrosa->N && currTime < milagrosa->M){
				_mngr->getComponent<ImageWithFrames>(e)->setFrame(15);
			}
			else if (currTime > milagrosa->M) {
				_mngr->getComponent<ImageWithFrames>(e)->setFrame(12);
			}
		}
	}
	
}

void FoodSystem::spawnFood() {

	int spaceBetweenX = sdlutils().width() / 8; //px
	int spaceBetweenY = sdlutils().height() / 6; //px
	// !! modificar para tamaño 25
	int s = 50; //px

	for (int i = 0; i < 8; i++) {
		auto x = (s / 2) + spaceBetweenX * i;
		for (int j = 0; j < 6; j++) {
			
			// ENTIDAD
			auto e = _mngr->addEntity(ecs::grp::FOOD);
			
			// TRANSFORM
			auto tr = _mngr->addComponent<Transform>(e);
			auto y = (s / 2) + spaceBetweenY * j;
			tr->init(Vector2D(x, y), Vector2D(0, 0), s, s, 0.0f);

			// MILAGROSA
			bool thisMilagrosa = (rand() % 100) < 10;
			auto milagrosa = _mngr->addComponent<Milagrosa>(e, thisMilagrosa);
			
			// IMAGE_WITH_FRAMES
			auto foodImage = _mngr->addComponent<ImageWithFrames>(e, &sdlutils().images().at("sprites"), 48, 8, 8);
			//foodImage->setFrame(milagrosa->milagrosa == false ? 12 : 15);
			foodImage->setFrame(12);
		}
	}
}
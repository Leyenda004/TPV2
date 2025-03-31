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
	auto currTime = sdlutils().virtualTimer().currTime() / 1000;
	auto foods = _mngr->getEntities(ecs::grp::FOOD);
	//auto n = foods.size();

	int i = 0;
	for (auto e : foods) {
		auto milagrosa = _mngr->getComponent<Milagrosa>(e);
		if (milagrosa->milagrosa){
			if (currTime > milagrosa->N && currTime < milagrosa->M){
				std::cout << i << " -- N: " << milagrosa->N << " M: " << milagrosa->M << std::endl;
				_mngr->getComponent<ImageWithFrames>(e)->setFrame(15);
			}
			else if (currTime > milagrosa->M) {
				_mngr->getComponent<ImageWithFrames>(e)->setFrame(12);
			}
		}
		i++;
	}
	
}

void FoodSystem::spawnFood() {

	float spaceBetweenX = sdlutils().width() / 8+2; //px
	float spaceBetweenY = sdlutils().height() / 6+2; //px
	// !! modificar para tamaño 25
	float s = 25; //px

	for (int i = 0; i < 8; i++) {
		float x = s + spaceBetweenX * i;
		for (int j = 0; j < 6; j++) {
			
			// ENTIDAD
			auto e = _mngr->addEntity(ecs::grp::FOOD);
			
			// TRANSFORM
			auto tr = _mngr->addComponent<Transform>(e);
			float y = s + spaceBetweenY * j;
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
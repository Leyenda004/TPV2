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
	
}

void FoodSystem::update() {
	auto currTime = sdlutils().virtualTimer().currTime() / 1000; // tiempo actual en segundos
	auto foods = _mngr->getEntities(ecs::grp::FOOD);

	for (auto e : foods) {
		auto milagrosa = _mngr->getComponent<Milagrosa>(e);
		if (milagrosa->milagrosa) {
			if (!milagrosa->isActive) {
				if ((currTime - milagrosa->timer) >= milagrosa->N) {
					milagrosa->isActive = true;
					milagrosa->timer = currTime; // reinicia el timer al activarse
					milagrosa->fruitChanged = true;
					_mngr->getComponent<ImageWithFrames>(e)->setFrame(15);
				} else {
					milagrosa->fruitChanged = false;
					_mngr->getComponent<ImageWithFrames>(e)->setFrame(12);
				}
			} else {
				if ((currTime - milagrosa->timer) >= milagrosa->M) {
					milagrosa->isActive = false;
					milagrosa->fruitChanged = false;
					milagrosa->timer = currTime; // empieza a contar para la siguiente aparición
					_mngr->getComponent<ImageWithFrames>(e)->setFrame(12);
				} else {
					milagrosa->fruitChanged = true;
					_mngr->getComponent<ImageWithFrames>(e)->setFrame(15);
				}
			}
		}
	}
}

void FoodSystem::spawnFood() 
{
	_aliveFruits = 0;

	float spaceBetweenX = sdlutils().width() / 8+2; //px
	float spaceBetweenY = sdlutils().height() / 6+2; //px
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

			++_aliveFruits;
		}
	}
}

void FoodSystem::reset()
{
	for(auto food : _mngr->getEntities(ecs::grp::FOOD))
	{
		_mngr->setAlive(food, false);
	}
}

void FoodSystem::onFoodEaten(ecs::entity_t e)
{
	sdlutils().soundEffects().at("pacman_eat").play();
	
	_mngr->setAlive(e, false);

	--_aliveFruits; // !!!!!
	// _aliveFruits -= 5;

	if (_aliveFruits <= 0)
	{
		Message m;
		m.id = _m_GAME_OVER;
		m.game_over_data.playerWon = true;
		_mngr->send(m);

		Game::Instance()->setState(Game::GAMEOVER);
	}
}

void FoodSystem::resetMilagrosasTimers() {
	auto currTime = sdlutils().virtualTimer().currTime() / 1000; // tiempo actual
	auto foods = _mngr->getEntities(ecs::grp::FOOD);
	for (auto e : foods) {
		auto milagrosa = _mngr->getComponent<Milagrosa>(e);
		if (milagrosa && milagrosa->milagrosa) {
			milagrosa->resetTimer();
			milagrosa->timer = currTime; // reinicia el timer al tiempo actual
			milagrosa->isActive = false;
			milagrosa->fruitChanged = false;
			_mngr->getComponent<ImageWithFrames>(e)->setFrame(12);
		}
	}
}

void FoodSystem::recieve(const Message& m)
{
	switch (m.id) {
	case _m_PACMAN_FOOD_COLLISION:
		onFoodEaten(m.food_eaten_data.e);
		break;
	case _m_NEW_GAME:
		reset();
		spawnFood();
		break;
	case _m_ROUND_START:
		resetMilagrosasTimers();
		break;
	default:
		break;
	}
}
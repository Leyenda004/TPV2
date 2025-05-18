#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <cassert>
#include <random>
#include <cstdint>

struct Milagrosa: public ecs::Component {
	bool milagrosa;
	bool fruitChanged;
	bool isActive;
	uint32_t N; // tiempo hasta aparecer
	uint32_t M; // tiempo visible
	uint32_t timer; // timer interno

	Milagrosa(bool _milagrosa)
		: milagrosa(_milagrosa), fruitChanged(false), isActive(false), N(0), M(0), timer(0)
	{
		if (milagrosa){
			resetTimer();
		}
	}
	virtual ~Milagrosa() {}

	void resetTimer() {
		N = 10 + (rand() % 1000) / 100; // entre 10 y 20 segundos
		M = 1 + (rand() % 5); // entre 1 y 5 segundos
		timer = 0;
		fruitChanged = false;
		isActive = false;
	}
};
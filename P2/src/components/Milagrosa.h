#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <cassert>
#include <random>
#include <cstdint>

struct Milagrosa: public ecs::Component {

	Milagrosa(bool _milagrosa) : milagrosa(_milagrosa)
	{
		if (milagrosa){
			// N = 10 + (rand() % 1000) / 100; // 10 (iniciales) + n entre 0 y 1000 (ms) / 10 (s)
			// M = N + (2 + rand() % 3); // N + 2 (al menos 2s en pantalla) + ran(0,1,2)s para llegar a 5

			N = 10 + (rand() % 1000) / 100; // N entre 10 y 20 (segundos)
			M = N + 1 + (rand() % 5); // M entre 1 y 5 (segundos)

		}
	}
	virtual ~Milagrosa() {}

	bool milagrosa = false;
	bool fruitChanged = false;
	uint32_t N = 0;
	uint32_t M = 0;
};
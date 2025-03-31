#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <cassert>
#include <random>

struct Milagrosa: public ecs::Component {

	Milagrosa(bool _milagrosa) : milagrosa(_milagrosa)
	{
		if (milagrosa){
			N = 10 + (rand() % 1000) / 100; // 10 (iniciales) + n entre 0 y 1000 (ms) / 10 (s)
			M = N + (2 + rand() % 3); // N + 2 (al menos 2s en pantalla) + ran(0,1,2)s para llegar a 5
		}
	}

	virtual ~Milagrosa() {}

	bool milagrosa = false;
	float N = 0.0f;
	float M = 0.0f;
};


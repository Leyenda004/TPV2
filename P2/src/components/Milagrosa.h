#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <cassert>

struct Milagrosa: public ecs::Component {

	Milagrosa(bool _milagrosa = false) : milagrosa(_milagrosa)
	{}

	virtual ~Milagrosa() {}

	bool milagrosa = false;
	float N = 0.0f;
	float M = 0.0f;
};


#pragma once
#include "../ecs/Component.h"

struct Health : public ecs::Component {
	Health() : vida(3) { }
	Health(int _vida) : vida(_vida) { }

	virtual ~Health() {}

	void healthUpdate(int n) {
		vida += n;
		if (vida < 0) {
			vida = 0;
		}
		if (vida > 3) {
			vida = 3;
		}
	}

	int vida = 3;
};
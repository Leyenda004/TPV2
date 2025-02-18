#pragma once
#include "../ecs/Component.h"

#include "../utils//Vector2D.h"
#include <array>

class Gun : public ecs::Component {
public:
	// ... 
	struct Bullet {
		bool used = false;
		Vector2D pos;
		Vector2D vel;
		int width;
		int height;
		float rot;
	};
	constexpr static uint8_t _max_bullets = 20;
	typedef std::array<Bullet, _max_bullets> bullets_array_t;
	typedef bullets_array_t::iterator iterator;
	void reset();
	iterator begin() {
		return _bullets.begin();
	}
	iterator end() {
		return _bullets.end();
	}
	// ... 
private:
	void shoot(Vector2D p, Vector2D v, int width, int height, float r);
	bullets_array_t _bullets;
	// ...   
};
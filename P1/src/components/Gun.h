#pragma once
#include "../ecs/Component.h"

#include "../utils//Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include <array>

class Transform;

class Gun : public ecs::Component {

public:
	__CMPID_DECL__(ecs::cmp::GUN)

	Gun() {};
	virtual ~Gun() {};

	void initComponent() override;
	void update() override;	
	void reset();
	void render() override;

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


	int itNum = 0;
	iterator begin() {
		return _bullets.begin();
	}
	iterator end() {
		return _bullets.end();
	}
private:
	void handleInput();
	Transform* _tr;
	Texture* _bulletTex;

	void shoot(Vector2D p, Vector2D v, int width, int height, float r);
	bullets_array_t _bullets;

	int nextShoot = 0;
	bool allBulletsUsed();

};
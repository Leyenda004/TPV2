#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Health : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::HEALTH)

	Health();
	Health(int lifeMax);

	void initComponent() override;
	void render() override;

	inline int getLifeValue() {
		return _lifeNum;
	}

	inline void lifeReset() {
		_lifeNum = _lifeMax;
	}

	inline void subtractLife() {
		--_lifeNum;
		if (_lifeNum < 0) _lifeNum = 0;
	}

private:

	int _lifeNum;
	int _lifeMax;
	
	Texture* _healthTex;
};


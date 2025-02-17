#pragma once
#include "../ecs/Component.h"

class Transform;

class DeAcceleration : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::DEACCELERATION)
	void update() override;
	void initComponent() override;

private:
	Transform* _tr;
};


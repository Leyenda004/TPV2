#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform;

class TowardDestination : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::TOWARD_DESTINATION)

	TowardDestination();
	virtual	~TowardDestination(){}

	void initComponent() override;
	void update() override;

protected:

	void setRandomDestination();

	Vector2D _targetPos;
	Transform* _mTransform;
};
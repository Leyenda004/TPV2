#pragma once
#include "../ecs/Component.h"

class Transform;

class FighterCtrl : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::FIGHTERCTRL)
	float thrust = 0.2f;
	float speedLimit = 3.0f;

	FighterCtrl() {};
	virtual ~FighterCtrl() {};

	void initComponent() override;
	void update() override;

private:
	void handleInput();
	Transform* _tr;
};
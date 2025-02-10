#pragma once
#include "InputComponent.h"
class FighterCtrl : public InputComponent
{
	float thrust = 0.2f;
	float speedLimit = 3.0f;
	void handleInput(Container*) override;
};
#pragma once
#include "FighterFacade.h"
#include "../components/Transform.h"
class FighterUtils : public FighterFacade
{
public:
	FighterUtils();
	void create_fighter() override;
	void reset_fighter() override;
	void reset_lives() override;
	int update_lives(int n) override;
private:
	ecs::Manager* _mngr;
	Transform* tr;
};


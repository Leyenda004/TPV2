#include "FighterUtils.h"

#include "Game.h"
#include "../components/Transform.h"

#include "../components/DeAcceleration.h"
#include "../components/FighterCtrl.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Health.h"
#include "../components/ImageWithFrames.h"
#include "../components/Image.h"
#include "../components/Gun.h"

FighterUtils::FighterUtils()
{
	std::cout << "antes de constructor fighterutils" << std::endl;
	_mngr = Game::Instance()->getMngr();
	std::cout << "después de constructor fighterutils" << std::endl;
}

void FighterUtils::create_fighter()
{
	auto fighter = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::FIGHTER, fighter);

	auto* tr = _mngr->addComponent<Transform>(fighter);

	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;

	tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	_mngr->addComponent<DeAcceleration>(fighter);
	//_mngr->addComponent<ImageWithFrames>(fighter/*, &sdlutils().images().at("fighter")*/);
	_mngr->addComponent<Image>(fighter, &sdlutils().images().at("fighter"));
	_mngr->addComponent<FighterCtrl>(fighter);
	_mngr->addComponent<ShowAtOppositeSide>(fighter);
	_mngr->addComponent<Health>(fighter);
	_mngr->addComponent<Gun>(fighter);
}

void FighterUtils::reset_fighter()
{

}

void FighterUtils::reset_lives()
{

}

int FighterUtils::update_lives(int n)
{
	return 0;
}

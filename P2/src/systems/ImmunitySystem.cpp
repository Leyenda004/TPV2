#include "ImmunitySystem.h"

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

void ImmunitySystem::initSystem()
{

}

void ImmunitySystem::update()
{
	if (_pacmanIsImmune && sdlutils().virtualTimer().currTime() - _immunityInnitTime > _immunityDurationTime)
	{
		_pacmanIsImmune = false;

		Message m;
		m.id = _m_IMMUNITY_END;
		_mngr->send(m);
	}std::cout << _pacmanIsImmune << "\n";
}

void ImmunitySystem::recieve(const Message& m)
{
	if(m.id == _m_PACMAN_FOOD_COLLISION && m.food_eaten_data.miraculous && !_pacmanIsImmune)
	{
		_pacmanIsImmune = true;
		_immunityInnitTime = sdlutils().virtualTimer().currTime();

		Message m;
		m.id = _m_IMMUNITY_START;
		_mngr->send(m);
	}
}
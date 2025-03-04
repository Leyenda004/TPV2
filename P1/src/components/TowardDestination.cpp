#include "TowardDestination.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

TowardDestination::TowardDestination()
{
	setRandomDestination();
}

void TowardDestination::initComponent()
{
	_mTransform = _ent->getMngr()->getComponent<Transform>(_ent);
	assert(_mTransform != nullptr);
}

void TowardDestination::update()
{
	// Indicaciones del Campus Virtual
	// v.rotate(v.angle(q-p))     p su posición, y q la posición del caza
	_mTransform->getVel() = _mTransform->getVel().rotate(
		_mTransform->getVel().angle(_targetPos - _mTransform->getPos()));
}

void TowardDestination::setRandomDestination()
{
	int randomX = sdlutils().rand().nextInt(0, sdlutils().width());
	int randomY = sdlutils().rand().nextInt(0, sdlutils().height());

	_targetPos = Vector2D(randomX, randomY);
}
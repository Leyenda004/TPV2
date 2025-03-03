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
	// v.rotate(v.angle(q-p))     p su posici�n, y q la posici�n del caza
	_mTransform->getVel() = _mTransform->getVel().rotate(
		_mTransform->getVel().angle(_targetPos - _mTransform->getPos()));
}

void TowardDestination::setRandomDestination()
{
	_targetPos = Vector2D();
}
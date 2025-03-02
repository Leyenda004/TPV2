#include "Follow.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

Follow::Follow(Transform* fighterTr) : _fighterTr(fighterTr)
{

}

Follow::Follow() : _fighterTr(nullptr)
{

}

void Follow::initComponent()
{
	_mTransform = _ent->getMngr()->getComponent<Transform>(_ent);
	assert(_mTransform != nullptr);
}

void Follow::update()
{
	if (_fighterTr == nullptr) return;

	// Indicaciones del Campus Virtual
	// v.rotate(v.angle(q-p) > 0 ? 1.0f : -1.0f)     p su posición, y q la posición del caza

	_mTransform->getVel().rotate(
		_mTransform->getVel().angle(_fighterTr->getVel() - _mTransform->getVel()) > 0 ? 1.0f : -1.0f);
}

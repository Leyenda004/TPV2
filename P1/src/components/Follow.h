#include "../ecs/Component.h"

class Transform;

class Follow : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::FOLLOW)

	Follow();
	Follow(Transform* fighterTr);
	virtual ~Follow(){}

	void initComponent() override;
	void update() override;

protected:

	Transform* _fighterTr;
	Transform* _mTransform;
};
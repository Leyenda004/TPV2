#include "../ecs/Component.h"

class Generations : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::GENERATIONS)

	Generations();
	Generations(int nGenerations);
	virtual ~Generations(){}

	int getGenerations() { return _nGenerations; }
	void setGenerations(int generations);

protected:

	int _nGenerations;
};
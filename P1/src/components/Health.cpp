#include "Health.h"

Health::Health(int lifeMax = 3) : _lifeMax(lifeMax), _lifeNum(lifeMax)
{

}

Health::Health() : Health(3)
{

}
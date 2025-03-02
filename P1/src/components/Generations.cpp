#include "Generations.h"

Generations::Generations()
{
	_nGenerations = 1;
}

Generations::Generations(int nGenerations)
{
	setGenerations(nGenerations);
}

void Generations::setGenerations(int generations)
{
	_nGenerations = generations;

	if (_nGenerations < 1) _nGenerations = 1;
}

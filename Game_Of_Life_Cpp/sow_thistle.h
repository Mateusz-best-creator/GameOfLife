#pragma once

#pragma once

#include "plant.h"

class SowThistle : public Plant
{
public:
	SowThistle(int, int);
	~SowThistle();
	void action(char**, int, int) override;
};
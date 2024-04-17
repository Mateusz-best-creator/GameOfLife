#pragma once

#include "plant.h"

class Grass : public Plant
{
public:
	Grass(int, int);
	~Grass();
	void action(char**, int, int) override;
};
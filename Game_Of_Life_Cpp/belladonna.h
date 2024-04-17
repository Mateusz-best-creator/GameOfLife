#pragma once

#include "plant.h"

class Belladonna : public Plant
{
public:
	Belladonna(int, int);
	~Belladonna();
	void action(char**, int, int) override;
};
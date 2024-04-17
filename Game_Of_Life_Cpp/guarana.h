#pragma once

#include "plant.h"

class Guarana : public Plant
{
public:
	Guarana(int, int);
	~Guarana();
	void action(char**, int, int) override;
};
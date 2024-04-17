#pragma once

#include "animal.h"

class Sheep : public Animal
{
public:
	Sheep(int, int);
	Sheep(int, int, int, int);
	~Sheep();
	void action(char** board, int height, int width) override;
};
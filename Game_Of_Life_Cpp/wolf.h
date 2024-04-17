#pragma once

#include "animal.h"

class Wolf : public Animal
{
public:
	Wolf(int, int);
	Wolf(int, int, int, int);
	~Wolf();
	void action(char** board, int height, int width) override;
};
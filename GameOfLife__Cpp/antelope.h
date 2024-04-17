#pragma once

#include "animal.h"

class Antelope : public Animal
{
public:
	Antelope(int, int);
	Antelope(int, int, int, int);
	~Antelope();
	void action(char** board, int height, int width) override;
};
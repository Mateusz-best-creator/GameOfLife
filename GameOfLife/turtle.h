#pragma once

#include "animal.h"

class Turtle : public Animal
{
public:
	Turtle(int, int);
	Turtle(int, int, int, int);
	~Turtle();
	void action(char** board, int height, int width) override;
};
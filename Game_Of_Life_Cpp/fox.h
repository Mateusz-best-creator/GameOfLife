#pragma once

#include "animal.h"

class Fox : public Animal
{
public:
	Fox(int, int);
	Fox(int, int, int, int);
	~Fox();
	void action(char** board, int height, int width) override;
	bool fox_can_go(char c) const;
};
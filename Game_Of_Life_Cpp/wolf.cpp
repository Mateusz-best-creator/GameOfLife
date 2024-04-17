#include "wolf.h"
#include <iostream>

Wolf::Wolf(int row, int column)
	: Animal("wolf", row, column)
{
	get_strength() = 9;
	get_initiative() = 5;
	get_type() = OrganismType::Wolf;
}

Wolf::Wolf(int strength, int initiative, int row, int column)
	: Animal("wolf", row, column)
{
	get_strength() = strength;
	get_initiative() = initiative;
}

Wolf::~Wolf() {}

void Wolf::action(char** board, int height, int width)
{
	Animal::default_action(board, height, width);
}
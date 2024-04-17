#include "sheep.h"
#include <iostream>

Sheep::Sheep(int row, int column)
    : Animal("sheep", row, column)
{
    get_strength() = 4;
    get_initiative() = 4;
    get_type() = OrganismType::Sheep;
}

Sheep::Sheep(int strength, int initiative, int row, int column)
    : Animal("sheep", row, column)
{
    get_strength() = strength;
    get_initiative() = initiative;
}

Sheep::~Sheep() {}

void Sheep::action(char** board, int height, int width)
{
    Animal::default_action(board, height, width);
}
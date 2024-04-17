#include "turtle.h"
#include <iostream>

Turtle::Turtle(int row, int column)
    : Animal("turtle", row, column)
{
    get_strength() = 2;
    get_initiative() = 1;
    get_type() = OrganismType::Turtle;
}

Turtle::Turtle(int strength, int initiative, int row, int column)
    : Animal("sheep", row, column)
{
    get_strength() = strength;
    get_initiative() = initiative;
}


Turtle::~Turtle() {}

void Turtle::action(char** board, int height, int width)
{
    int randomNum = rand() % 4 + 1;
    if (randomNum != 4)
        std::cout << get_name() << " stays at the same position: (" << get_position_row() << ", " << get_position_column() << ")\n";
    else
        Animal::default_action(board, height, width);
}

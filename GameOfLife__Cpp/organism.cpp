#include "organism.h"
#include <iostream>

int Organism::num_of_organisms = 0;

Organism::Organism(int row, int column, std::string n)
    : position_row(row), position_column(column), name(n)
{
    age = 0;
    num_of_organisms++;
    index = num_of_organisms;
    if (n == "Guarana")
        character = 'U';
    else if (n == "Sosnowsky_hogweed")
        character = 'O';
    else
        character = n[0];
}

Organism::~Organism()
{

}
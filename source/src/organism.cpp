#include "organism.h"
#include <iostream>

Organism::Organism(int row, int column, std::string n)
    : position_row(row), position_column(column), name(n) 
{
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
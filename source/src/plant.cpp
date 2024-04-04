#include "plant.h"

Plant::Plant(const std::string& n, int row, int column)
    : Organism(row, column, n)
{
    std::string name = get_name();
    if (name == "Grass")
        strength = 0;
    else if (name == "Sow_thistle")
        strength = 0;
    else if (name == "Guarana")
        strength = 0;
    else if (name == "Belladonna")
        strength = 99;
    else
        strength = 10;
}

Plant::~Plant()
{

}

void Plant::action(int height, int width)
{

}

void Plant::collision(char** board, std::vector<Organism*>& organisms)
{

}

char Plant::draw() const
{
    return get_character();
}
#include "animal.h"

Animal::Animal(std::string n, int row, int column)
    : Organism(row, column, n[0])
{
    name = n;
    if (name == "wolf")
    {
        strength = 9;
        initiative = 5;
    }
    else if (name == "sheep")
    {
        strength = 4;
        initiative = 4;
    }
    else if (name == "fox")
    {
        strength = 3;
        initiative = 7;
    }
    else if (name == "turtle")
    {
        strength = 2;
        initiative = 1;
    }
    else if (name == "antelope")
    {
        strength = 4;
        initiative = 4;
    }
    else if (name == "cyber_sheep")
    {
        strength = 11;
        initiative = 4;
    }
    else // human
    {
        strength = 5;
        initiative = 4;
    }
}

Animal::~Animal()
{

}

void Animal::action(int height, int width)
{

}

void Animal::collision()
{

}

char Animal::draw() const
{
    return get_character();
}
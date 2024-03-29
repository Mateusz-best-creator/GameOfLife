#include "plant.h"
#include "organism_info.h"

Plant::Plant(std::string n)
{
    name = n;
    PlantInfo obj = plantsInfo[n];
    character = obj.character;
    strength = obj.strength;
}

Plant::~Plant()
{

}

void Plant::action()
{

}

void Plant::collision()
{

}

char Plant::draw() const
{
    return character;
}
#include "animal.h"
#include "organism_info.h"

Animal::Animal(std::string n)
{
    name = n;
    AnimalInfo obj = animalsInfo[n];
    character = obj.character;
    initiative = obj.initiative;
    strength = obj.strength;
}

Animal::~Animal()
{

}

void Animal::action()
{

}

void Animal::collision()
{

}

char Animal::draw() const
{
    return character;
}
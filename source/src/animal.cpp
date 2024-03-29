#include "animal.h"

Animal::Animal(char ch)
    : character(ch)
{

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
#pragma once

#include "organism.h"

class Animal : public Organism
{
private:
    char character;

public:
    Animal(char);
    ~Animal();

    virtual void action() override;
    virtual void collision() override;
    virtual char draw() const override;

};
#pragma once

#include "organism.h"
#include <string>


class Plant : public Organism
{
private:
    std::string name;
    char character;
    int strength;
    const int initiative = 0;

public:
    Plant(std::string n, int, int);
    ~Plant();

    virtual void action() override;
    virtual void collision() override;
    virtual char draw() const override;

};
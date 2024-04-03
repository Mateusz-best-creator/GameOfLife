#pragma once

#include "organism.h"
#include <string>

enum class AnimalTypes { WOLF, SHEEP, FOX, TURTLE, ANTELOPE, CYBER_SHEEP };

class Animal : public Organism
{
private:
    std::string name;
    int strength, initiative;

public:
    Animal(std::string, int, int);
    ~Animal();

    virtual void action() override;
    virtual void collision() override;
    virtual char draw() const override;

    const int& get_initiative() const override { return initiative; }
};
#pragma once

#include "organism.h"
#include <string>
#include <vector>

enum class AnimalTypes { WOLF, SHEEP, FOX, TURTLE, ANTELOPE, CYBER_SHEEP };

class Animal : public Organism
{
private:
    int strength, initiative;

public:
    Animal(std::string, int, int);
    ~Animal();

    virtual void action(int, int) override;
    virtual void collision(char**, std::vector<Organism*>&) override;
    virtual char draw() const override;

    const int& get_initiative() const override { return initiative; }
    void default_action(int, int, char**);
};
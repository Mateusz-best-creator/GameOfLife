#pragma once

#include "organism.h"
#include <string>
#include <vector>


class Animal : public Organism
{
private:
    int initiative, strength;

public:
    Animal(std::string, int, int);
    ~Animal();

    virtual void action(int, int) override;
    virtual void collision(char**, std::vector<Organism*>&) override;
    virtual char draw() const override;

    int& get_initiative() { return initiative; }
    const int& get_initiative() const { return initiative; }
    int& get_strength() { return strength; }
    const int& get_strength() const { return strength; }

    void default_action(int, int, char**);
};
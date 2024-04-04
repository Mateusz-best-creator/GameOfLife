#pragma once

#include "animal.h"
#include <vector>

class Human : public Animal
{
private:
    const int human_strength = 5, human_initiative = 4;
    char direction;
    int counter = 0;
    bool ability_activated = false;
    
public:
    Human(std::string, int, int);
    ~Human();

    virtual void action(int, int) override;
    virtual void collision(char**, std::vector<Organism*>&) override;

    char& set_direction() { return direction; }
    const char& get_direction() const { return direction; }
};
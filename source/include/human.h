#pragma once

#include "animal.h"

class Human : public Animal
{
private:
    const int human_strength = 5, human_initiative = 4;
    char direction;
    
public:
    Human(std::string, int, int);
    ~Human();

    virtual void action(int, int) override;

    char& set_direction() { return direction; }
    const char& get_direction() const { return direction; }
};
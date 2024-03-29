#pragma once

#include "animal.h"

class Human : public Animal
{
private:
    const int human_strength = 5, human_initiative = 4;
    
public:
    Human(std::string, int, int);
    ~Human();

    virtual void action() override;
};
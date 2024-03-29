#pragma once

#include "animal.h"

class Human : public Animal
{
public:
    Human(char);
    ~Human();

    virtual void action() override;
};
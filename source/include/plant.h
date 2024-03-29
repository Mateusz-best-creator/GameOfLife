#pragma once

#include "organism.h"

class Plant : public Organism
{
private:
    char character;

public:
    Plant(char);
    ~Plant();

    virtual void action() override;
    virtual void collision() override;
    virtual char draw() const override;

};
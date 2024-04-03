#pragma once

#include "organism.h"
#include <string>

enum class PlantTypes { GRASS, SOW_THISTLE, GUARANA, BELLADONNA, SOSNOWSKY_HOGWEED };

class Plant : public Organism
{
private:
    std::string name;
    int strength;
    const int initiative = 0;

public:
    Plant(const std::string&, int, int);
    ~Plant();

    virtual void action(int, int) override;
    virtual void collision() override;
    virtual char draw() const override;
    const int& get_initiative() const override { return initiative; }
};
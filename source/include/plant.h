#pragma once

#include "organism.h"
#include <string>
#include <vector>

class Plant : public Organism
{
private:
    int strength;
    const int initiative = 0;

public:
    Plant(const std::string&, int, int);
    ~Plant();

    virtual void action(int, int) override;
    virtual void collision(char**, std::vector<Organism*>&) override;
    virtual char draw() const override;
    
    const int& get_initiative() const { return initiative; }
    int& get_strength() { return strength; }
    const int& get_strength() const { return strength; }
};
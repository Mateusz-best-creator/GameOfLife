#pragma once

#include "organism.h"
#include <string>
#include <vector>

class Plant : public Organism
{
private:
    int strength;
    const int initiative = 0;

    const float probability = 0.1; // 10 percent probability
    bool can_sow = false;

public:
    Plant(const std::string&, int, int);
    Plant(const std::string&, int, int, int, int);
    ~Plant();

    virtual void action(char**, int, int) override;
    virtual void collision(char**, std::vector<Organism*>&, std::vector<int>&, std::vector<PlaceToAddOrganism>&) override;
    virtual char draw() const override;
    
    const int& get_initiative() const { return initiative; }
    int& get_strength() { return strength; }
    const int& get_strength() const { return strength; }

    void default_action();
    void sow_thistle_action();
    void sosnowsky_hogweed_action();

    void sosnowsky_collision(int, int, int, int, std::vector<Organism*>&, std::vector<int>&);
};
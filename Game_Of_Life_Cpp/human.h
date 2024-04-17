#pragma once

#include "animal.h"
#include <vector>
#include <string>

class Human : public Animal
{
private:
    const int human_strength = 5, human_initiative = 4;
    char direction = 'T';
    int counter = 5;
    bool ability_activated = false;

    enum ArrowKey : char { UP = 'A', BOTTOM = 'B', LEFT = 'D', RIGHT = 'C', SPECIAL_ACTIVITY = 'S', STAYS = 'T' };
    std::string OS;

public:
    Human(int, int);
    Human(int, int, int, int);
    ~Human();

    virtual void action(char**, int, int) override;
    virtual void collision(char**, std::vector<Organism*>&, std::vector<int>&, std::vector<PlaceToAddOrganism>&) override;

    char& set_direction() { return direction; }
    const char& get_direction() const { return direction; }
};
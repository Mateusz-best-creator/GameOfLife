#pragma once

#include "organism.hpp"

class Plant : public Organism
{
private:
    const float SOW_PROBABILITY = 0.1;

public:
    Plant(int, int, int, std::string, char, int, int, std::string, OrganismType);

    virtual ActionResult action(std::vector<std::vector<char>>&) override = 0;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override = 0;
    virtual int get_static_counter() override = 0;

    ActionResult default_action_plant(std::vector<std::vector<char>>&);
    CollisionResult default_collision_plant();
};

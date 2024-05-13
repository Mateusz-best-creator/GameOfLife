#pragma once

#include <vector>
#include "organism.hpp"

class Animal : public Organism
{
public:
    Animal(int, int, std::string, char, int, int, std::string, OrganismType);

    virtual ActionType action(std::vector<std::vector<char>>&) override = 0;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override = 0;
    virtual int get_static_counter() override = 0;

    ActionType default_action_animal(std::vector<std::vector<char>>&);
    CollisionResult default_collision_animal(std::vector<std::vector<char>>&, std::vector<Organism*>&, int);
};
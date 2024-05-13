#pragma once

#include "animal.hpp"

class Human : public Animal
{
private:
    static int HUMAN_STATIC_COUNTER;

public:
    Human(int, int, int strength = 5, int initiative = 4);
    ~Human();

    virtual ActionType action(std::vector<std::vector<char>>&) override final;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override final;
    virtual int get_static_counter() override final;
};
#pragma once

#include "animal.hpp"

class Sheep : public Animal
{
private:
    static int SHEEP_STATIC_COUNTER;

public:
    Sheep(int, int);
    Sheep(int, int, int, int, int);
    ~Sheep();

    virtual ActionResult action(std::vector<std::vector<char>>&) override final;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override final;
    virtual int get_static_counter() override final;
};
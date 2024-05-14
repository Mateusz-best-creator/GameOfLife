#pragma once

#include "plant.hpp"

class Grass : public Plant
{
private:
    static int GRASS_STATIC_COUNTER;

public:
    Grass(int, int);
    Grass(int, int, int, int, int);
    ~Grass();

    virtual ActionResult action(std::vector<std::vector<char>>&) override final;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override final;
    virtual int get_static_counter() override final;
};

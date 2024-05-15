#pragma once

#include "plant.hpp"

class SowThistle : public Plant
{
private:
    static int SOW_THISTLE_STATIC_COUNTER;

public:
    SowThistle(int, int);
    SowThistle(int, int, int, int, int);
    ~SowThistle();

    virtual ActionResult action(std::vector<std::vector<char>>&) override final;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override final;
    virtual int get_static_counter() override final;
};

#pragma once

#include "plant.hpp"

class Belladonna : public Plant
{
private:
    static int BELLADONNA_STATIC_COUNTER;

public:
    Belladonna(int, int);
    Belladonna(int, int, int, int, int);
    ~Belladonna();

    virtual ActionResult action(std::vector<std::vector<char>>&) override final;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override final;
    virtual int get_static_counter() override final;
};

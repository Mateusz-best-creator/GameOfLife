#pragma once

#include "animal.hpp"

class Antelope : public Animal
{
private:
    static int ANTELOPE_STATIC_COUNTER;

public:
    Antelope(int, int);
    Antelope(int, int, int, int, int);
    ~Antelope();

    virtual ActionResult action(std::vector<std::vector<char>>&) override final;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override final;
    virtual int get_static_counter() override final;
};
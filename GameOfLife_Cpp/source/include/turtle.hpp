#pragma once

#include "animal.hpp"

class Turtle : public Animal
{
private:
    static int TURTLE_STATIC_COUNTER;

public:
    Turtle(int, int);
    Turtle(int, int, int, int, int);
    ~Turtle();

    virtual ActionResult action(std::vector<std::vector<char>>&) override final;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override final;
    virtual int get_static_counter() override final;
};
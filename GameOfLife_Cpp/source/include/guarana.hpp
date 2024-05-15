#pragma once

#include "plant.hpp"

class Guarana : public Plant
{
private:
    static int GUARANA_STATIC_COUNTER;

public:
    Guarana(int, int);
    Guarana(int, int, int, int, int);
    ~Guarana();

    virtual ActionResult action(std::vector<std::vector<char>>&) override final;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override final;
    virtual int get_static_counter() override final;
};

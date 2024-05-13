#pragma once

#include "animal.hpp"

class Wolf : public Animal
{
private:
    static int WOLF_STATIC_COUNTER;

public:
    Wolf(int, int);
    ~Wolf();

    virtual ActionType action(std::vector<std::vector<char>>&) override final;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override final;
    virtual int get_static_counter() override final;
};
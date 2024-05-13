#pragma once

#include "animal.hpp"

class Fox : public Animal
{
private:
    static int FOX_STATIC_COUNTER;

public:
    Fox(int, int);
    ~Fox();

    virtual ActionType action(std::vector<std::vector<char>>&) override final;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override final;
    virtual int get_static_counter() override final;
};
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
    virtual CollisionType collision() override final;
    virtual int get_static_counter() override final;
};
#pragma once

#include "animal.hpp"

class CyberSheep : public Animal
{
private:
    static int CYBER_SHEEP_STATIC_COUNTER;

public:
    CyberSheep(int, int);
    CyberSheep(int, int, int, int, int);
    ~CyberSheep();

    virtual ActionResult action(std::vector<std::vector<char>>&) override final;
    virtual CollisionResult collision(std::vector<std::vector<char>>&, std::vector<Organism*>&, int) override final;
    virtual int get_static_counter() override final;
};
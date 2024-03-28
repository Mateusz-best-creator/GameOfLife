#pragma once
#include <vector>
#include "organism.h"

class World
{
private:
    std::vector<Organism> organisms;
    int height, width;

public:
    World(int, int);
    ~World();

    void makeTurn();
    void drawWorld() const;
    bool is_human_on_map() const;
};

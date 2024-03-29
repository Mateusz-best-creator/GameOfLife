#pragma once

#include <vector>
#include "organism.h"

const int KINDS_OF_ORGANISMS = 11;

class World
{
private:
    std::vector<Organism*> organisms;
    int height, width, number_of_organisms;
    const int max_organisms;

public:
    World(int, int);
    ~World();

    void makeTurn();
    void drawWorld() const;
    bool is_human_on_map() const;
};

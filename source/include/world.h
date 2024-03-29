#pragma once

#include <vector>
#include "organism.h"

const int KINDS_OF_ORGANISMS = 12;

class World
{
private:
    std::vector<Organism*> organisms;
    int height, width, number_of_organisms;
    const int max_organisms;
    char** board;

public:
    World(int, int);
    ~World();

    void makeTurn();
    void legend();
    void drawWorld() const;
    bool is_human_on_map() const;

    void add(std::vector<Organism*>& data, const std::string& name, int times, bool is_animal = true, bool is_human = false);
};

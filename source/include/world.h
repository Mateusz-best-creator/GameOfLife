#pragma once

#include <vector>
#include "organism.h"
#include <map>

const int KINDS_OF_ORGANISMS = 12;

class World
{
private:
    std::vector<Organism*> organisms;
    int height, width, number_of_organisms;
    const int max_organisms;
    char** board;

    enum class AnimalTypes {WOLF};

public:
    World(int, int);
    ~World();

    bool makeTurn();
    void legend();
    void update_world();
    void drawWorld() const;
    bool is_human_on_map() const;

    void add(std::vector<Organism*>& data, const std::string&, int times, bool is_animal = true, bool is_human = false);
};

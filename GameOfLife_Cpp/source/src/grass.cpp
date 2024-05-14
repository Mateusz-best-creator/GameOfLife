#include "grass.hpp"
#include <iostream>

int Grass::GRASS_STATIC_COUNTER = 0;

Grass::Grass(int row, int column)
    : Plant(0, 0, 0, "Grass", 'G', row, column, "grass.png", OrganismType::GRASS)
{
    GRASS_STATIC_COUNTER++;
}

Grass::Grass(int row, int column, int strength, int initiative, int age)
    : Plant(strength, initiative, age, "Grass", 'G', row, column, "grass.png", OrganismType::GRASS)
{
    GRASS_STATIC_COUNTER++;
}

Grass::~Grass()
{
    GRASS_STATIC_COUNTER--;
}

ActionResult Grass::action(std::vector<std::vector<char>>& grid_board)
{
    return this->default_action_plant(grid_board);
}

CollisionResult Grass::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_plant();
}

int Grass::get_static_counter()
{
    return GRASS_STATIC_COUNTER;
}
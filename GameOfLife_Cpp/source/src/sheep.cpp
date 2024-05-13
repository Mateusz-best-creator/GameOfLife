#include "sheep.hpp"

int Sheep::SHEEP_STATIC_COUNTER = 0;

Sheep::Sheep(int row, int column)
    : Animal(4, 4, "sheep", 's', row, column, "sheep.png", OrganismType::SHEEP)
{
    SHEEP_STATIC_COUNTER++;  
}

Sheep::~Sheep()
{
    SHEEP_STATIC_COUNTER--;
}

ActionType Sheep::action(std::vector<std::vector<char>>& grid_board)
{
    return Animal::default_action_animal(grid_board);
}

CollisionResult Sheep::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_animal(grid_board, organisms, current_index);
}

int Sheep::get_static_counter()
{
    return SHEEP_STATIC_COUNTER;
}
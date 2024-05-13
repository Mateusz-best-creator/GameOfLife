#include "fox.hpp"

int Fox::FOX_STATIC_COUNTER = 0;

Fox::Fox(int row, int column)
    : Animal(3, 7, "fox", 'f', row, column, "fox.png", OrganismType::FOX)
{
    FOX_STATIC_COUNTER++;
}

Fox::~Fox()
{
    FOX_STATIC_COUNTER--;
}

ActionType Fox::action(std::vector<std::vector<char>>& grid_board)
{
    return Animal::default_action_animal(grid_board);
}

CollisionResult Fox::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_animal(grid_board, organisms, current_index);
}

int Fox::get_static_counter()
{
    return FOX_STATIC_COUNTER;
}
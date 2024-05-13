#include "wolf.hpp"

int Wolf::WOLF_STATIC_COUNTER = 0;

Wolf::Wolf(int row, int column)
    : Animal(9, 5, "wolf", 'w', row, column, "wolf.png", OrganismType::WOLF)
{
    WOLF_STATIC_COUNTER++;  
}

Wolf::~Wolf()
{
    WOLF_STATIC_COUNTER--;
}

ActionType Wolf::action(std::vector<std::vector<char>>& grid_board)
{
    return Animal::default_action_animal(grid_board);
}

CollisionResult Wolf::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_animal(grid_board, organisms, current_index);
}

int Wolf::get_static_counter()
{
    return WOLF_STATIC_COUNTER;
}
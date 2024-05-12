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

Organism::ActionType Wolf::action(std::vector<std::vector<char>>& grid_board)
{
    Animal::default_action_animal(grid_board);
}

Organism::CollisionType Wolf::collision()
{

}

int Wolf::get_static_counter()
{
    return WOLF_STATIC_COUNTER;
}
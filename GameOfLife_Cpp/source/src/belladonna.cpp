#include "belladonna.hpp"

int Belladonna::BELLADONNA_STATIC_COUNTER = 0;

Belladonna::Belladonna(int row, int column)
    : Plant(99, 0, 0, "Belladonna", 'B', row, column, "belladonna.png", OrganismType::BELLADONNA)
{
    BELLADONNA_STATIC_COUNTER++;
}

Belladonna::Belladonna(int row, int column, int strength, int initiative, int age)
    : Plant(strength, initiative, age, "Belladonna", 'B', row, column, "belladonna.png", OrganismType::BELLADONNA)
{
    BELLADONNA_STATIC_COUNTER++;
}

Belladonna::~Belladonna()
{
    BELLADONNA_STATIC_COUNTER--;
}

ActionResult Belladonna::action(std::vector<std::vector<char>>& grid_board)
{
    return this->default_action_plant(grid_board);
}

CollisionResult Belladonna::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_plant();
}

int Belladonna::get_static_counter()
{
    return BELLADONNA_STATIC_COUNTER;
}
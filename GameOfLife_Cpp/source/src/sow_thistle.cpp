#include "sow_thistle.hpp"

int SowThistle::SOW_THISTLE_STATIC_COUNTER = 0;

SowThistle::SowThistle(int row, int column)
    : Plant(0, 0, 0, "SowThistle", 'S', row, column, "sow_thistle.png", OrganismType::SOW_THISTLE)
{
    SOW_THISTLE_STATIC_COUNTER++;
}

SowThistle::SowThistle(int row, int column, int strength, int initiative, int age)
    : Plant(strength, initiative, age, "SowThistle", 'S', row, column, "sow_thistle.png", OrganismType::SOW_THISTLE)
{
    SOW_THISTLE_STATIC_COUNTER++;
}

SowThistle::~SowThistle()
{
    SOW_THISTLE_STATIC_COUNTER--;
}

ActionResult SowThistle::action(std::vector<std::vector<char>>& grid_board)
{
    return this->default_action_plant(grid_board);
}

CollisionResult SowThistle::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_plant();
}

int SowThistle::get_static_counter()
{
    return SOW_THISTLE_STATIC_COUNTER;
}
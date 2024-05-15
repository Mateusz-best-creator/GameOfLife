#include "guarana.hpp"

int Guarana::GUARANA_STATIC_COUNTER = 0;

Guarana::Guarana(int row, int column)
    : Plant(0, 0, 0, "Guarana", 'U', row, column, "guarana.png", OrganismType::GUARANA)
{
    GUARANA_STATIC_COUNTER++;
}

Guarana::Guarana(int row, int column, int strength, int initiative, int age)
    : Plant(strength, initiative, age, "Guarana", 'U', row, column, "guarana.png", OrganismType::GUARANA)
{
    GUARANA_STATIC_COUNTER++;
}

Guarana::~Guarana()
{
    GUARANA_STATIC_COUNTER--;
}

ActionResult Guarana::action(std::vector<std::vector<char>>& grid_board)
{
    return this->default_action_plant(grid_board);
}

CollisionResult Guarana::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_plant();
}

int Guarana::get_static_counter()
{
    return GUARANA_STATIC_COUNTER;
}
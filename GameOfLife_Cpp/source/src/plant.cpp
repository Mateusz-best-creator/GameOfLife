#include "plant.hpp"
#include <cassert>
#include <iostream>

Plant::Plant(int strength, int initiative, int age, std::string name, char character, int row, int column, std::string image_name, OrganismType type)
    : Organism(strength, initiative, age, name, character, row, column, image_name, type)
{
    
}

ActionResult Plant::default_action_plant(std::vector<std::vector<char>>& grid_board)
{
    int random = rand() % 100 + 1;
    if (random >= this->SOW_PROBABILITY * 100)
        return ActionResult(ActionType::STAY);
    if (this->get_static_counter() >= MAX_ORGANISM_AMOUNT)
    {
        std::cout << "Cannot create another " << this->get_name() << ", we already have " << this->get_static_counter() << " of them at the board...\n";
        return ActionResult(ActionType::STAY);
    }
    std::cout << this->get_name() << " will sow around (" << row << ", " << column << ")\n";
    return ActionResult(ActionType::SOW, Point(row, column), this->get_type());
}

CollisionResult Plant::default_collision_plant()
{
    return CollisionResult(CollisionType::NONE);
}
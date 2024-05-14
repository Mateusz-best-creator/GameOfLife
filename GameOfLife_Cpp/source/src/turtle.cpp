#include "turtle.hpp"
#include <iostream>

int Turtle::TURTLE_STATIC_COUNTER = 0;

Turtle::Turtle(int row, int column)
    : Animal(2, 1, 0, "turtle", 't', row, column, "turtle.png", OrganismType::TURTLE)
{
    TURTLE_STATIC_COUNTER++;  
}

Turtle::Turtle(int row, int column, int strength, int initiative, int age)
    : Animal(strength, initiative, age, "turtle", 't', row, column, "turtle.png", OrganismType::TURTLE)
{
    TURTLE_STATIC_COUNTER++;  
    this->get_age() = age;
}

Turtle::~Turtle()
{
    TURTLE_STATIC_COUNTER--;
}

ActionResult Turtle::action(std::vector<std::vector<char>>& grid_board)
{
    previous_row = row;
    previous_column = column;
    int random = rand() % 4 + 1;
    if (random == 4)
        return Animal::default_action_animal(grid_board);
    std::cout << this->get_name() << " stays at the same position: (" << row << ", " << column << ")\n";
    return ActionResult(ActionType::STAY);
}

CollisionResult Turtle::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_animal(grid_board, organisms, current_index);
}

int Turtle::get_static_counter()
{
    return TURTLE_STATIC_COUNTER;
}
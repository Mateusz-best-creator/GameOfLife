#include "animal.hpp"
#include <cassert>
#include <iostream>

Animal::Animal(int strength, int initiative, std::string name, char character, int row, int column, std::string image_name, OrganismType type)
    : Organism(strength, initiative, name, character, row, column, image_name, type)
{
    
}

Organism::ActionType Animal::default_action_animal(std::vector<std::vector<char>>& grid_board)
{
    this->previous_row = this->row;
    this->previous_column = this->column;
    grid_board[previous_row][previous_column] = 'e';

    Direction direction = static_cast<Direction>((rand()%4)+1);
    while (true)
    {
        if ((this->row == 0 && direction == Direction::TOP)
            || (this->row == BOARD_HEIGHT - 1 && direction == Direction::BOTTOM)
            || (this->column == 0 && direction == Direction::LEFT)
            || (this->column == BOARD_WIDTH - 1 && direction == Direction::RIGHT))
        {
            direction = static_cast<Direction>((rand()%4)+1);
        }
        else
        {
            break;
        }
    }

    switch (direction)
    {
        case Direction::LEFT:
            this->move_left();
            break;
        case Direction::TOP:
            this->move_top();
            break;
        case Direction::RIGHT:
            this->move_right();
            break;
        case Direction::BOTTOM:
            this->move_bottom();
            break;
        default:
            std::cout << "Invalid direction at default_animal_action(...)\n";
            break;
    }

    this->move_message();
    assert(this->row >= 0 && this->row < BOARD_HEIGHT && this->column >= 0 && this->column < BOARD_WIDTH);
    grid_board[this->row][this->column] = this->get_character();
    return ActionType::MOVE;
}

Organism::CollisionType Animal::default_collision_animal()
{
    
}
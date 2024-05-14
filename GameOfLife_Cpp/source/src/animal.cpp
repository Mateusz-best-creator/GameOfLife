#include "animal.hpp"
#include <cassert>
#include <iostream>

Animal::Animal(int strength, int initiative, int age, std::string name, char character, int row, int column, std::string image_name, OrganismType type)
    : Organism(strength, initiative, age, name, character, row, column, image_name, type)
{
    
}

ActionResult Animal::default_action_animal(std::vector<std::vector<char>>& grid_board)
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
            direction = static_cast<Direction>((rand()%4)+1);
        else
            break;
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
    return ActionResult(ActionType::MOVE);
}

CollisionResult Animal::default_collision_animal(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    int index = 0;
    std::vector<int> indexes;
    for (auto organism : organisms)
    {
        // We found collision with another organism
        if (organism->get_row() == this->row && organism->get_column() == this->column && index != current_index)
        {
            // Multiplication case
            if (organism->get_type() == this->get_type())
            {
                std::cout << this->get_name() << " multiplication at (" << this->row << ", " << column << ") " 
                << this->get_name() << " goes back to (" << this->previous_row << ", " << this->previous_column << ")\n";
                int original_row = row;
                int original_col = column;
                row = previous_row;
                column = previous_column;
                assert(row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH);
                grid_board[row][column] = this->get_character();

                // Check for max amount
                if (this->get_static_counter() > MAX_ORGANISM_AMOUNT)
                {
                    std::cout << "Cannot add more " << this->get_name() << ", we arleady have " << this->get_static_counter() << " of them on the board...\n";
                    return CollisionResult(CollisionType::NONE);
                }

                return CollisionResult(CollisionType::MULTIPLICATION, Point(original_row, original_col), this->get_type());
            }
            // Turtle collision case
            else if (organism->get_type() == OrganismType::TURTLE && this->get_strength() < 5)
            {
                std::cout << organism->get_name() << " reflects the attack at (" << this->row << ", " << column << ") " 
                << this->get_name() << " goes back to (" << previous_row << ", " << previous_column << ")\n";
                grid_board[row][column] = 't';
                row = previous_row;
                column = previous_column;
                grid_board[row][column] = this->get_character();
                return CollisionResult(CollisionType::NONE);
            }
            // Fight case
            else if (organism->get_type() != this->get_type())
            {
                if (this->get_strength() >= organism->get_strength())
                {
                    std::cout << this->get_name() << " wins with " << organism->get_name() << " at (" << this->row << ", " << column << ")\n";
                    indexes.push_back(index);
                    grid_board[row][column] = this->get_character();
                }
                else 
                {
                    std::cout << organism->get_name() << " wins with " << this->get_name() << " at (" << this->row << ", " << column << ")\n";
                    indexes.push_back(current_index);
                    grid_board[row][column] = organism->get_character();
                }
                return CollisionResult(CollisionType::FIGHT, indexes);
            }
        }
        index++;
    }
    return CollisionResult(CollisionType::NONE);
}
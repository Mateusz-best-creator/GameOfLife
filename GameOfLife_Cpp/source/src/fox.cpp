#include "fox.hpp"
#include <iostream>
#include <cassert>

int Fox::FOX_STATIC_COUNTER = 0;

Fox::Fox(int row, int column)
    : Animal(3, 7, 0, "fox", 'f', row, column, "fox.png", OrganismType::FOX)
{
    FOX_STATIC_COUNTER++;
}

Fox::Fox(int row, int column, int strength, int initiative, int age)
    : Animal(strength, initiative, age, "fox", 'f', row, column, "fox.png", OrganismType::FOX)
{
    FOX_STATIC_COUNTER++;
}

Fox::~Fox()
{
    FOX_STATIC_COUNTER--;
}

ActionResult Fox::action(std::vector<std::vector<char>>& grid_board)
{
    previous_row = row;
    previous_column = column;
    const int DIRECTIONS_AMOUNT = 4;
    int random_start = rand() % DIRECTIONS_AMOUNT + 1;
    int rand_array[DIRECTIONS_AMOUNT];
    
    int j = 0;
    for (int i = random_start; i < random_start + DIRECTIONS_AMOUNT; i++)
        rand_array[j++] = i % DIRECTIONS_AMOUNT + 1;

    Direction dir = Direction::NONE;
    for (int i = 0; i < DIRECTIONS_AMOUNT; i++)
    {
        dir = static_cast<Direction>(rand_array[i]);
        bool moved = false;
        switch (dir)
        {
            case Direction::LEFT:
                if (column > 0 && fox_can_go(grid_board[row][column - 1]))
                {
                    this->move_left();
                    moved = true;
                }
                break;
            case Direction::TOP:
                if (row > 0 && fox_can_go(grid_board[row - 1][column]))
                {
                    this->move_top();
                    moved = true;
                }
                break;
            case Direction::RIGHT:
                if (column < BOARD_WIDTH - 1 && fox_can_go(grid_board[row][column + 1]))
                {
                    this->move_right();
                    moved = true;
                }
                else
                {
                    if (column < BOARD_WIDTH - 1)
                        std::cout << "Cant move right now! : " << grid_board[row][column + 1] << std::endl;
                }
                break;
            case Direction::BOTTOM:
                if (row < BOARD_HEIGHT - 1 && fox_can_go(grid_board[row + 1][column]))
                {
                    this->move_bottom();
                    moved = true;
                }
                break;
            case Direction::NONE:
            default:
                break;
        }
        if (moved)
            break;
        dir = Direction::NONE;
    }

    // Fox had no option to move
    if (dir == Direction::NONE)
    {
        std::cout << this->get_name() << " at (" << this->row << ", " << this->column << ") has no cell to move\n";
        return ActionType::STAY;
    }

    std::cout << this->get_name() << " moves from (" << previous_row << ", " << previous_column << ") to (" << row << ", " << column << ")\n";
    this->default_grid_update(grid_board);

    return ActionResult(ActionType::MOVE);
}

CollisionResult Fox::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_animal(grid_board, organisms, current_index);
}

int Fox::get_static_counter()
{
    return FOX_STATIC_COUNTER;
}

bool Fox::fox_can_go(char character) const
{
    return character == 't' || character == 'G' || character == 'U' || character == 'S' || character == 'e' || character == 'f';
}
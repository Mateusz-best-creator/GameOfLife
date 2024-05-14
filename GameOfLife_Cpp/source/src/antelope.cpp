#include "antelope.hpp"
#include <iostream>
#include <cassert>

int Antelope::ANTELOPE_STATIC_COUNTER = 0;

Antelope::Antelope(int row, int column)
    : Animal(4, 4, 0, "antelope", 'a', row, column, "antelope.png", OrganismType::ANTELOPE)
{
    ANTELOPE_STATIC_COUNTER++;  
}

Antelope::Antelope(int row, int column, int strength, int initiative, int age)
    : Animal(strength, initiative, age, "antelope", 'a', row, column, "antelope.png", OrganismType::ANTELOPE)
{
    ANTELOPE_STATIC_COUNTER++;  
}

Antelope::~Antelope()
{
    ANTELOPE_STATIC_COUNTER--;
}

ActionResult Antelope::action(std::vector<std::vector<char>>& grid_board)
{
    const int DIRECTIONS_AMOUNT = 4;
    int multiplier = rand() % 2 + 1;
    if (multiplier == 1)
        return Animal::default_action_animal(grid_board);
    int random_start = rand() % DIRECTIONS_AMOUNT + 1;
    int rand_array[DIRECTIONS_AMOUNT];
    
    int j = 0;
    for (int i = random_start; i < random_start + DIRECTIONS_AMOUNT; i++)
        rand_array[j++] = i % DIRECTIONS_AMOUNT + 1;
        
    bool moved = false;
    previous_row = row;
    previous_column = column;

    std::cout << get_name() << " moves from (" << row << ", " << column << ") to (";
    for (int i = 0; i < DIRECTIONS_AMOUNT; i++)
    {
        Direction dir = static_cast<Direction>(rand_array[i]);
        switch (dir)
        {
            case Direction::LEFT:
                if (column > 1)
                {
                    moved = true;
                    column -= 2;
                }
                break;
            case Direction::TOP:
                if (row > 1)
                {
                    moved = true;
                    row -= 2;
                }
                break;
            case Direction::RIGHT:
                if (column < BOARD_WIDTH - 2)
                {
                    moved = true;
                    column += 2;
                }
                break;
            case Direction::BOTTOM:
                if (row < BOARD_HEIGHT - 2)
                {
                    moved = true;
                    row += 2;
                }
                break;
            default:
                break;
        }
        if (moved)
            break;
    }
    assert(row != previous_row || column != previous_column);
    std::cout << row << ", " << column << ")\n";
    return ActionResult(ActionType::MOVE);
}

CollisionResult Antelope::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_animal(grid_board, organisms, current_index);
}

int Antelope::get_static_counter()
{
    return ANTELOPE_STATIC_COUNTER;
}
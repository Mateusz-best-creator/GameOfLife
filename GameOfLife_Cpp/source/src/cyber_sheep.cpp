#include "cyber_sheep.hpp"
#include <cmath>
#include <iostream>
#include <cassert>

int CyberSheep::CYBER_SHEEP_STATIC_COUNTER = 0;

CyberSheep::CyberSheep(int row, int column)
    : Animal(11, 4, 0, "cyber_sheep", 'c', row, column, "cyber_sheep.png", OrganismType::CYBER_SHEEP)
{
    CYBER_SHEEP_STATIC_COUNTER++;  
}

CyberSheep::CyberSheep(int row, int column, int strength, int initiative, int age)
    : Animal(strength, initiative, age, "cyber_sheep", 'c', row, column, "cyber_sheep.png", OrganismType::CYBER_SHEEP)
{
    CYBER_SHEEP_STATIC_COUNTER++;  
}

CyberSheep::~CyberSheep()
{
    CYBER_SHEEP_STATIC_COUNTER--;
}

ActionResult CyberSheep::action(std::vector<std::vector<char>>& grid_board)
{
    previous_row = row;
    previous_column = column;
    float shortest_distance = -1;
    int sosnowsky_row = - 1, sosnowsky_column = -1;

    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            // Check for sosnowsky hogweed
            if (grid_board[i][j] == 'O')
            {
                float distance = pow(row - i, 2) + pow(column - j, 2);
                if (distance < shortest_distance || shortest_distance == -1)
                {
                    shortest_distance = distance;
                    sosnowsky_row = i;
                    sosnowsky_column = j;
                }
            }
        }
    }

    if (sosnowsky_row == -1 || sosnowsky_column == -1)
        return Animal::default_action_animal(grid_board);

    if (sosnowsky_row > row)
        move_bottom();
    else if (sosnowsky_row < row)
        move_top();
    else if (sosnowsky_column > column)
        move_right();
    else if (sosnowsky_column < column)
        move_left();
    else
        return ActionResult(ActionType::STAY);
    std::cout << this->get_name() << " moves from (" << row <<", " << column << ")\n";
    this->default_grid_update(grid_board);
    return ActionResult(ActionType::MOVE);
}

CollisionResult CyberSheep::collision(std::vector<std::vector<char>>& grid_board, std::vector<Organism*>& organisms, int current_index)
{
    return this->default_collision_animal(grid_board, organisms, current_index);
}

int CyberSheep::get_static_counter()
{
    return CYBER_SHEEP_STATIC_COUNTER;
}
#include <iostream>
#include "cyber_sheep.h"
#include "animal.h"

CyberSheep::CyberSheep(int row, int column)
    : Animal("cyber_sheep", row, column)
{
    get_strength() = 11;
    get_initiative() = 4;
    get_type() = OrganismType::CyberSheep;
}

CyberSheep::CyberSheep(int strength, int initiative, int row, int column)
    : Animal("cyber_sheep", row, column)
{
    get_strength() = strength;
    get_initiative() = initiative;
}

CyberSheep::~CyberSheep() {}

void CyberSheep::action(char** board, int height, int width)
{
    int sosnowsky_row, sosnowsky_column;
    int row = this->get_position_row(), column = this->get_position_column();
    if (return_is_sosnowsky(board, sosnowsky_row, sosnowsky_column, height, width))
    {
        std::cout << this->get_name() << " moves from (" << this->get_position_row() << ", " << this->get_position_column() << ") to ";
        int row_diff = sosnowsky_row - row;
        int col_diff = sosnowsky_column - column;

        // Determine the direction
        if (row_diff < 0 && col_diff < 0)
        {
            // Move towards top-left
            this->get_position_column()--;
        }
        else if (row_diff < 0 && col_diff > 0)
        {
            // Move towards top-right
            this->get_position_column()++;
        }
        else if (row_diff > 0 && col_diff < 0)
        {
            // Move towards bottom-left
            this->get_position_row()++;
        }
        else if (row_diff > 0 && col_diff > 0)
        {
            // Move towards bottom-right
            this->get_position_row()++;
        }
        else if (row_diff < 0 && col_diff == 0)
        {
            // Move straight up
            this->get_position_row()--;
        }
        else if (row_diff > 0 && col_diff == 0)
        {
            // Move straight down
            this->get_position_row()++;
        }
        else if (row_diff == 0 && col_diff < 0)
        {
            // Move straight left
            this->get_position_column()--;
        }
        else if (row_diff == 0 && col_diff > 0)
        {
            // Move straight right
            this->get_position_column()++;
        }
        std::cout << "(" << this->get_position_row() << ", " << this->get_position_column() << ")\n";
    }
    else
        Animal::default_action(board, height, width);
}

bool CyberSheep::return_is_sosnowsky(char** board, int& row, int& col, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (board[i][j] == 'O')
            {
                row = i;
                col = j;
                return true;
            }
        }
    }

    return false;
}
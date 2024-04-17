#include "fox.h"
#include <iostream>
#include <set>

Fox::Fox(int row, int column)
    : Animal("fox", row, column)
{
    get_strength() = 3;
    get_initiative() = 7;
    get_type() = OrganismType::Fox;
}

Fox::Fox(int strength, int initiative, int row, int column)
    : Animal("sheep", row, column)
{
    get_strength() = strength;
    get_initiative() = initiative;
}

Fox::~Fox() {}

bool Fox::fox_can_go(char c) const
{
    return c == 't' || c == 'G' || c == 'S' || c == 'U' || c == ' ';
}

void Fox::action(char** board, int height, int width)
{
    using std::cout;
    using std::endl;

    std::set<Directions> s;

    Directions direction = static_cast<Directions>(rand() % 4);
    int row = this->get_position_row(), column = this->get_position_column();
    while (true)
    {
        if (row > 0 && direction == Directions::TOP)
        {
            char top_board = board[row - 1][column];
            if (fox_can_go(top_board))
            {
                get_position_row()--;
                cout << this->get_name() << " moves one square top to: (" << this->get_position_row() << ", " << this->get_position_column() << ")\n";
                return;
            }
        }
        else if (row < height - 1 && direction == Directions::BOTTOM)
        {
            char bottom_board = board[row + 1][column];
            if (fox_can_go(bottom_board))
            {
                get_position_row()++;
                cout << this->get_name() << " moves one square bottom to: (" << this->get_position_row() << ", " << this->get_position_column() << ")\n";
                return;
            }
        }
        else if (column > 0 && direction == Directions::LEFT)
        {
            char left_board = board[row][column - 1];
            if (fox_can_go(left_board))
            {
                get_position_column()--;
                cout << this->get_name() << " moves one square left to: (" << this->get_position_row() << ", " << this->get_position_column() << ")\n";
                return;
            }
        }
        else if (column < width - 1 && direction == Directions::RIGHT)
        {
            char right_board = board[row][column + 1];
            if (fox_can_go(right_board))
            {
                get_position_column()++;
                cout << this->get_name() << " moves one square right to: (" << this->get_position_row() << ", " << this->get_position_column() << ")\n";
                return;
            }
        }
        s.insert(direction);
        if (s.size() >= 4)
        {
            cout << "Fox cant move anywhere, it stays where it is: (" << row << ", " << column << ")\n";
            return;
        }
        direction = static_cast<Directions>(rand() % 4);
    }
}
#include <iostream>
#include "human.h"

Human::Human(std::string n, int row, int column)
    : Animal(n, row, column)
{

}

Human::~Human()
{

}

void Human::action(int height, int width)
{
    std::cout << "Pls dzialaj\n";

    // Tutaj jakos trzeba wczytac spacje
    char move;
    std::cout << "Enter human move: ";
    std::cin >> move; // narazie l, t, r, b

    switch (move)
    {
    case 'l':
        if (get_position_column() > 0)
        {
            std::cout << "Moving human player one square to the left\n";
            get_position_column()--;
        }
        else
            std::cout << "Cant move human player one square to the left\n";
        break;
    case 'r':
        if (get_position_column() < width - 1)
        {
            std::cout << "Moving human player one square to the right\n";
            get_position_column()++;
        }
        else
            std::cout << "Cant move human player one square to the right\n";
        break;
    case 't':
        if (get_position_row() > 0)
        {
            std::cout << "Moving human player one square to the top\n";
            get_position_row()--;
        }
        else
            std::cout << "Cant move human player one square to the top\n";
        break;
    case 'b':
        if (get_position_row() < height - 1)
        {
            std::cout << "Moving human player one square to the bottom\n";
            get_position_row()++;
        }
        else
            std::cout << "Cant move human player one square to the bottom\n";
        break;
    }
}
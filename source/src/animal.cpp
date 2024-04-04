#include "animal.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Animal::Animal(std::string n, int row, int column)
    : Organism(row, column, n)
{
    std::string name = get_name();
    if (name == "wolf")
    {
        strength = 9;
        initiative = 5;
    }
    else if (name == "sheep")
    {
        strength = 4;
        initiative = 4;
    }
    else if (name == "fox")
    {
        strength = 3;
        initiative = 7;
    }
    else if (name == "turtle")
    {
        strength = 2;
        initiative = 1;
    }
    else if (name == "antelope")
    {
        strength = 4;
        initiative = 4;
    }
    else if (name == "cyber_sheep")
    {
        strength = 11;
        initiative = 4;
    }
    else // human
    {
        strength = 5;
        initiative = 4;
    }
}

Animal::~Animal()
{

}

int random_number(int from, int to) 
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int randomNum = rand() % (to - from + 1) + from;
    return randomNum;
}

void Animal::action(int height, int width)
{
    using namespace std;
    std::string name = get_name();

    if (name == "wolf" || name == "sheep")
    {
        // default_action(height, width, board);
    }
    else if (name == "fox")
    {
        
    }
    else if (name == "turtle")
    {

    }
    else if (name == "antelope")
    {

    }
    else if (name == "cyber_sheep")
    {

    }
}

void Animal::collision(char** board, std::vector<Organism*>& organisms)
{
    
}

char Animal::draw() const
{
    return get_character();
}

void Animal::default_action(int height, int width, char** board)
{
    using namespace std;
    string name = get_name();
    int row = get_position_row();
    int column = get_position_column();
    int direction = random_number(1, 4);

    if (direction == 1 && get_position_column() > 0) // left
    {   
        cout << "Moving " << name << " one square to the left\n";
        if (board[row][column - 1] == ' ')
            get_position_column()--;
        else if (board[row][column - 1] == get_character())
        {
            // Multiplication case
            int neighbor = random_number(1, 2);
            if (neighbor == 1)
            {
                if (row > 0 && board[row - 1][column] == ' ');
            }
            else
            {

            }
        }
        else
        {
            // collision case

        }
    }
    else if (direction == 2 && get_position_row() > 0) // top
    {
        cout << "Moving " << name << " one square to the top\n";
        get_position_row()--;
    }
    else if (direction == 3 && get_position_column() < width - 1) // right
    {
        cout << "Moving " << name << " one square to the right\n";
        get_position_column()++;
    }
    else if (direction == 4 && get_position_row() < height - 1) // bottom
    {
        cout << "Moving " << name << " one square to the bottom\n";
        get_position_row()++;
    }
}
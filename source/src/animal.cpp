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
        default_action(name, height, width);
    else if (name == "fox")
        fox_action(name, height, width);
    else if (name == "turtle")
        turtle_action(name, height, width);
    else if (name == "antelope")
        antelope_action(name, height, width);
    else if (name == "cyber_sheep")
        cyber_sheel_action(name, height, width);
}

char Animal::draw() const
{
    return get_character();
}

/*
    All animal actions implementation
*/

void Animal::default_action(std::string name, int height, int width) {
    using namespace std;

    // Get the current position
    int& current_row = get_position_row();
    int& current_column = get_position_column();

    while (true) 
    {
        // Generate a random number between 0 and 3 to represent the four directions
        int direction = rand() % 4;

        // Update the position based on the randomly chosen direction
        switch (direction) 
        {
            case 0: // Move left
                if (current_column > 0) 
                {
                    cout << name << " from (" << current_row << ", " << current_column << ") moving one square to the left\n";
                    get_position_column()--;
                    previous_move = 0;
                    return;
                }
                break;
            case 1: // Move top
                if (current_row > 0) 
                {
                    cout << name << " from (" << current_row << ", " << current_column << ") moving one square to the top\n";
                    get_position_row()--;
                    previous_move = 1;
                    return;
                }
                break;
            case 2: // Move right
                if (current_column < width - 1) 
                {
                    cout << name << " from (" << current_row << ", " << current_column << ") moving one square to the right\n";
                    get_position_column()++;
                    previous_move = 2;
                    return;
                }
                break;
            case 3: // Move bottom
                if (current_row < height - 1) 
                {
                    cout << name << " from (" << current_row << ", " << current_column << ") moving one square to the bottom\n";
                    get_position_row()++;
                    previous_move = 3;
                    return;
                }
                break;
            default:
                cout << "Invalid direction\n";
                break;
        }
    }
}

void Animal::fox_action(std::string name, int height, int width)
{

}

void Animal::turtle_action(std::string name, int height, int width)
{
    
}

void Animal::antelope_action(std::string name, int height, int width)
{
    
}

void Animal::cyber_sheel_action(std::string name, int height, int width)
{
    
}

bool is_within_board(int row, int column, int height, int width)
{
    return row >= 0 && row < height && height >= 0 && column < width;
}

/*
    Function that will handle collisions between animals
*/
void Animal::collision(char** board, std::vector<Organism*>& organisms)
{
    int height = sizeof(board) / sizeof(board[0]);
    int width = sizeof(board[0]) / sizeof(char);

    using namespace std;
    int row = get_position_row(), column = get_position_column();
    if (board[row][column] == ' ')
        return;

    
    for (size_t i = 0; i < organisms.size(); i++)
    {
        auto organism = organisms[i];
        // We found collisions
        if (organism->get_position_row() == row && organism->get_position_column() == column)
        {
            // Multiplication case
            if (organism->get_character() == get_character())
            {
                cout << "Multiplication case!\n";

                if (previous_move == 0) get_position_column()--;
                else if (previous_move == 1) get_position_row()--;
                else if (previous_move == 2) get_position_column()++;
                else if (previous_move == 3) get_position_row()++;

                // Find an empty neighboring cell
                int new_row = get_position_row();
                int new_column = get_position_column();

                // Check neighboring cells in all directions
                for (int direction = 0; direction < 4; direction++)
                {
                    int new_row_attempt = new_row;
                    int new_column_attempt = new_column;

                    // Update position based on direction
                    if (direction == 0) // Up
                        new_row_attempt--;
                    else if (direction == 1) // Right
                        new_column_attempt++;
                    else if (direction == 2) // Down
                        new_row_attempt++;
                    else // Left
                        new_column_attempt--;

                    // Check if the new position is within the bounds of the board and is empty
                    if (is_within_board(new_row_attempt, new_column_attempt, height, width) && board[new_row_attempt][new_column_attempt] == ' ')
                    {
                        new_row = new_row_attempt;
                        new_column = new_column_attempt;
                        break; // Found an empty neighboring cell, no need to check further
                    }
                }

                cout << "Creating " << get_name() << " at: (" << new_row << ", " << new_column << ")" << std::endl; 
                // Add the new organism to the organisms vector
                organisms.insert(organisms.begin() + i, new Animal(get_name(), new_row, new_column));

                // Update the board to reflect the new organism
                board[new_row][new_column] = get_character();
            }
            // turtle case
            else if (organism->get_character() == 't')
            {
                std::cout << "Fight against " << get_name() << " and " << organisms[i]->get_name() << "..." << std::endl;
                
                if (previous_move == 0) get_position_column()--;
                else if (previous_move == 1) get_position_row()--;
                else if (previous_move == 2) get_position_column()++;
                else get_position_row()++;

                std::cout << "Turtle reflects the attack! " << get_name() 
                << " is going back to: (" << get_position_row() << ", " << get_position_column() << ")\n";
            }
            // fight case
            else
            {
                std::cout << "Fight against " << get_name() << " and " << organisms[i]->get_name() << "..." << std::endl;
                // winning case
                if (get_strength() >= organism->get_strength())
                {
                    cout << get_name() << " wins the battle!\n";
                    delete organisms[i];
                    organisms.erase(organisms.begin() + i);
                    return;
                }

                cout << organism->get_name() << " wins the battle!\n";
                for (size_t j = 0; j < organisms.size(); j++)
                {
                    if (organisms[j]->get_name() == get_name() && organisms[j]->get_position_row() == row && organisms[j]->get_position_column() == column)
                    {
                        delete organisms[j];
                        organisms.erase(organisms.begin() + j);
                        return;
                    }
                }
            }
        }
    }
    
}
#include <iostream>
#include <ncurses.h>
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
    using namespace std;
    
    // Get the current position
    int& current_row = get_position_row();
    int& current_column = get_position_column();

    // Prompt for human move
    char move;
    cout << "Enter human move (l for left, r for right, t for top, b for bottom, s for special ability): ";
    cin >> move;

    cout << "\nJournal:\n\n";

    // Show the current position before moving
    cout << "Starting human position: (" << current_row << ", " << current_column << ")" << endl;

    switch (move) 
    {
        case 'l':
            if (current_column > 0) 
            {
                cout << "Moving human player one square to the left\n";
                current_column--;
            } 
            else
                cout << "Can't move human player one square to the left\n";
            break;
        case 'r':
            if (current_column < width - 1) 
            {
                cout << "Moving human player one square to the right\n";
                current_column++;
            } 
            else
                cout << "Can't move human player one square to the right\n";
            break;
        case 't':
            if (current_row > 0) 
            {
                cout << "Moving human player one square to the top\n";
                current_row--;
            } 
            else
                cout << "Can't move human player one square to the top\n";
            break;
        case 'b':
            if (current_row < height - 1) 
            {
                cout << "Moving human player one square to the bottom\n";
                current_row++;
            } 
            else
                cout << "Can't move human player one square to the bottom\n";
            break;
        case 's':
            cout << "Special human ability activated!\n";
            ability_activated = true;
            counter = 5;
            break;
        default:
            cout << "Invalid move\n";
            break;

        counter--;
        if (!counter)
            ability_activated = false;
    }
    // Show the position after moving
    cout << "New human position: (" << current_row << ", " << current_column << ")" << endl;
}

void Human::collision(char** board, std::vector<Organism*>& organisms)
{
    int human_row = get_position_row(), human_column = get_position_column();
    // Board is not updated yet
    if (board[human_row][human_column] == ' ')
        return;
    
    for (size_t i = 0; i < organisms.size(); i++)
    {   
        // Colision with other organism
        if (organisms[i]->get_position_row() == human_row && organisms[i]->get_position_column() == human_column && organisms[i]->get_name() != "Human")
        {
            if (ability_activated)
            {
                delete organisms[i];
                organisms.erase(organisms.begin() + i);
            }
            else if (board[human_row][human_column] == 't') // turtle case
            {
                for (size_t i = 0; i < sizeof(board); i++)
                {
                    for (size_t j = 0; j < sizeof(board[0]); j++)
                    {
                        if (board[i][j] == 'H')
                        {
                            get_position_row() = i;
                            get_position_column() = j;
                            std::cout << "Turtle defends from human attack! Human is going back to " << i << ", " << j << std::endl;
                            return;
                        }
                    }
                }
            }
            else
            {
                std::cout << "Fight against Human and " << organisms[i]->get_name() << std::endl;
                // In case of equal strengths attacker wins
                if (human_strength >= organisms[i]->get_strength())
                {
                    std::cout << "Human win!\n";
                    delete organisms[i];
                    organisms.erase(organisms.begin() + i);
                    return;
                }
                
                std::cout << organisms[i]->get_name() << " win!\n";
                for (size_t i = 0; i < organisms.size(); i++)
                {
                    if (organisms[i]->get_name() == "Human")
                    {
                        delete organisms[i];
                        organisms.erase(organisms.begin() + i);
                    }
                }
                return;
            }
        } 
    }
}
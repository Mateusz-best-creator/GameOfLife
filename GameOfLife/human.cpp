#include <iostream>
#include <conio.h>
#include "human.h"

std::string getOS() 
{
#if defined(__linux__)
    std::cout << "Hello, GNU/Linux!" << '\n';
    return "linux";
#elif defined(_WIN32)
    std::cout << "Hello, Windows!" << '\n';
    return "windows";
#endif
}

Human::Human(int row, int column)
    : Animal("Human", row, column)
{
    this->get_strength() = 5;
    this->get_initiative() = 4;
    get_type() = OrganismType::Human;
}

Human::Human(int s, int i, int row, int column)
    : Animal("Human", s, i, row, column) {}

Human::~Human() {}

void Human::action(char** b, int height, int width)
{
    using namespace std;
    OS = getOS();
    this->get_type() = OrganismType::Human;
    // Get the current position
    int& current_row = get_position_row();
    int& current_column = get_position_column();

    cout << "Enter human move (arrow keys to control human movement): ";

    ArrowKey key = STAYS;
    if (OS == "linux")
    {
        char c = getchar();
        if (c == '\033')
        {
            getchar(); // skip the [
            int value = getchar();
            key = static_cast<ArrowKey>(value);
            fputs("\n", stdin);
        }
        else if (c == 's' || c == 'S')
            key = SPECIAL_ACTIVITY;
        else if (c == 't')
            key = STAYS;
    }
    else if (OS == "windows")
    {
        int ch = _getch();
        if (ch == 224)
        {
            ch = _getch();
            switch (ch)
            {
            case 72: key = UP;   break;
            case 80: key = BOTTOM;  break;
            case 77: key = RIGHT; break;
            case 75: key = LEFT;  break;
            }
        }
    }
    
    cout << "\nJournal:\n\n";

    // Show the current position before moving
    cout << "Starting human position: (" << current_row << ", " << current_column << ")" << endl;
   
    switch (key)
    {
    case UP:
        if (current_row > 0)
        {
            cout << "Moving human player one square to the top\n";
            current_row--;
            previous_move = Directions::TOP;
        }
        else
            cout << "Can't move human player one square to the top\n";
        break;
    case BOTTOM:
        if (current_row < height - 1)
        {
            cout << "Moving human player one square to the bottom\n";
            current_row++;
            previous_move = Directions::BOTTOM;
        }
        else
            cout << "Can't move human player one square to the bottom\n";
        break;
    case LEFT:
        if (current_column > 0)
        {
            cout << "Moving human player one square to the left\n";
            current_column--;
            previous_move = Directions::LEFT;
        }
        else
            cout << "Can't move human player one square to the left\n";
        break;
    case RIGHT:
        if (current_column < width - 1)
        {
            cout << "Moving human player one square to the right\n";
            current_column++;
            previous_move = Directions::RIGHT;
        }
        else
            cout << "Can't move human player one square to the right\n";
        break;
    case SPECIAL_ACTIVITY:
        if (counter == 5)
        {
            cout << "Special human ability activated!\n";
            ability_activated = true;
        }
        else if (ability_activated)
            cout << "Human special ability is arleady activated\n";
        else
            cout << "Cant activate special ability now, you have to wait " << 5 - counter << " turns\n";
        break;
    case STAYS:
        cout << this->get_name() << " stays at its current position: (" << this->get_position_row() << ", " << this->get_position_column() << endl;
        break;
    }

    if (ability_activated) counter--;
    else if (!ability_activated && counter != 5) counter++;
    if (!counter)
    {
        ability_activated = false;
        cout << "Human special activity deactivated\n";
    }

    // Show the position after moving
    cout << "New human position: (" << current_row << ", " << current_column << ")" << endl;
}

void get_dimensions(char** board, int& height, int& width)
{
    int h = 0, w = 0;
    while (board[h] != NULL)
        h++;
    while (board[0][w] != '\0')
        w++;
    height = h;
    width = w;
}

/*
    This collision function is very similar to Animal::collision function however for
    my convenience I decided to copy some things and apply some changes specific
    for Human type in this function.
*/
void Human::collision(char** board, std::vector<Organism*>& organisms, std::vector<int>& indexes_to_remove, std::vector<PlaceToAddOrganism>&)
{

    int row = get_position_row(), column = get_position_column();
    using namespace std;

    int height, width;
    get_dimensions(board, height, width);

    // Board is not updated yet
    if (board[row][column] == ' ')
        return;

    for (int i = 0; i < organisms.size(); i++)
    {
        auto organism = organisms[i];

        if (organism->get_position_row() == row
            && organism->get_position_column() == column
            && organism->get_index() != this->get_index())
        {
            cout << "Collision " << this->get_name() << " with " << organism->get_name() << " at (" << row << ", " << column << ")" << endl;

            if (organism->get_name() != "turtle")
            {
                // Antelope can escape from fight
                double probability = (rand() % 100 + 1) / 100.0;
                if (probability < 0.5 && organism->get_name() == "antelope")
                {
                    cout << organism->get_name() << " escapes from fight! ";
                    for (int newRow = row - 1; newRow <= row + 1; ++newRow)
                    {
                        for (int newColumn = column - 1; newColumn <= column + 1; ++newColumn)
                        {
                            if (newRow >= 0 && newRow < height && newColumn >= 0
                                && newColumn < width
                                && board[newRow][newColumn] == ' '
                                && (newRow != row && newColumn != column))
                            {
                                organism->get_position_row() = newRow;
                                organism->get_position_column() = newColumn;
                                cout << "It goes back to (" << organism->get_position_row() << ", " << organism->get_position_column() << ")\n";
                                return;
                            }
                        }
                    }
                }

                if (this->get_strength() >= organism->get_strength())
                {
                    cout << this->get_name() << " wins the battle with " << organism->get_name() << " at (" << row << ", " << column << ")\n";
                    indexes_to_remove.push_back(i);
                    return;
                }
                else
                {
                    cout << organism->get_name() << " wins the battle with " << this->get_name() << " at (" << row << ", " << column << ")\n";
                    if (ability_activated)
                    {
                        cout << "Beacuse of human special activity: IMMORTALITY, human is being moved to random square: ";
                        int new_row = rand() % height, new_column = rand() % width;
                        while (board[new_row][new_column] != ' ')
                        {
                            new_row = rand() % height;
                            new_column = rand() % width;
                        }
                        this->get_position_row() = new_row;
                        this->get_position_column() = new_column;
                        cout << "(" << new_row << ", " << new_column << ")\n";
                    }
                    else
                    {
                        for (int k = 0; k < organisms.size(); k++)
                        {
                            if (this->get_index() == organisms[k]->get_index())
                            {
                                indexes_to_remove.push_back(k);
                                return;
                            }
                        }
                    }
                }
            }
            else if (organism->get_name() == "turtle")
            {
                update_previous_move();
                cout << "Turtle defends from human attack at (" << row << ", " << column << "), Human is going back to ("
                    << this->get_position_row() << ", " << get_position_column() << ")" << endl;
            }
        }
    }
}
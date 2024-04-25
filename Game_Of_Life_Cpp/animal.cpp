#include "animal.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

Animal::Animal(std::string n, int row, int column)
    : Organism(row, column, n)
{
    std::string name = get_name();
}

Animal::Animal(std::string n, int s, int i, int row, int column)
    : Organism(row, column, n), strength(s), initiative(i)
{
    get_position_row() = row;
    get_position_column() = column;
}

Animal::~Animal()
{

}

void Animal::action(char** board, int height, int width)
{
    this->get_age() += 1;
    this->action(board, height, width);
}

void Animal::default_action(char** board, int height, int width)
{
    using std::cout;

    // Get the current position
    int& current_row = get_position_row();
    int& current_column = get_position_column();

    while (true)
    {
        // Generate a random number between 0 and 3 to represent the four directions
        int d = rand() % 4;
        Directions direction = static_cast<Directions>(d);
        std::string name = get_name();
        // Update the position based on the randomly chosen direction
        switch (direction)
        {
        case Directions::LEFT:
            if (current_column > 0)
            {
                cout << name << " from (" << current_row << ", " << current_column << ") moving one square to the left\n";
                get_position_column()--;
                previous_move = Directions::LEFT;
                return;
            }
            break;
        case Directions::TOP: // Move top
            if (current_row > 0)
            {
                cout << name << " from (" << current_row << ", " << current_column << ") moving one square to the top\n";
                get_position_row()--;
                previous_move = Directions::TOP;
                return;
            }
            break;
        case Directions::RIGHT: // Move right
            if (current_column < width - 1)
            {
                cout << name << " from (" << current_row << ", " << current_column << ") moving one square to the right\n";
                get_position_column()++;
                previous_move = Directions::RIGHT;
                return;
            }
            break;
        case Directions::BOTTOM: // Move bottom
            if (current_row < height - 1)
            {
                cout << name << " from (" << current_row << ", " << current_column << ") moving one square to the bottom\n";
                get_position_row()++;
                previous_move = Directions::BOTTOM;
                return;
            }
            break;
        default:
            cout << "Invalid direction\n";
            previous_move = Directions::NONE;
            break;
        }
    }
}

char Animal::draw() const
{
    return get_character();
}

/*
    Function that will handle collisions between animals
*/
void Animal::collision(char** board, std::vector<Organism*>& organisms, std::vector<int>& indexes_to_remove, std::vector<PlaceToAddOrganism>& organisms_to_add)
{
    using namespace std;

    int row = get_position_row(), column = get_position_column();
    if (board[row][column] == ' ')
        return;

    for (int i = 0; i < organisms.size(); i++)
    {
        auto organism = organisms[i];
        // We found collisions
        if (organism->get_position_row() == row
            && organism->get_position_column() == column
            && this->get_index() != organism->get_index())
        {
            cout << "Collision " << this->get_name() << " with " << organism->get_name() << " at (" << row << ", " << column << ")" << endl;

            // Fight case
            if (this->get_name() != organism->get_name() && organism->get_name() != "turtle")
            {
                double probability = (rand() % 100 + 1) / 100.0;
                if (probability < 0.5 && this->get_name() == "antelope")
                {
                    cout << this->get_name() << " escapes from fight! ";
                    update_previous_move();
                    cout << "It goes back to (" << this->get_position_row() << ", " << this->get_position_column() << ")\n";
                    return;
                }
                else if (probability < 0.5 && organism->get_name() == "antelope")
                {
                    cout << this->get_name() << " escapes from fight! ";
                    for (int newRow = row - 1; newRow <= row + 1; ++newRow)
                    {
                        for (int newColumn = column - 1; newColumn <= column + 1; ++newColumn)
                        {
                            if (newRow >= 0 && newRow < this->get_height() && newColumn >= 0 && newColumn < this->get_width() && board[newRow][newColumn] == ' ')
                            {
                                organism->get_position_row() = newRow;
                                organism->get_position_column() = newColumn;
                                cout << "It goes back to (" << organism->get_position_row() << ", " << organism->get_position_column() << ")\n";
                                return;
                            }
                        }
                    }
                }

                if (this->get_strength() >= organism->get_strength() && organism->get_name() != "Belladonna")
                {
                    cout << this->get_name() << " wins the battle with " << organism->get_name() << " at (" << row << ", " << column << ")\n";
                    if (organism->get_name() == "Human" && organism->get_special_activity() == true)
                    {
                        cout << "Beacuse of human special activity: IMMORTALITY, human is being moved to random square: ";
                        int new_row = rand() % (this->get_height() - 1);
                        int new_column = rand() % (this->get_width() - 1);
                        while (board[new_row][new_column] != ' ')
                        {
                            new_row = rand() % (this->get_height() - 1);
                            new_column = rand() % (this->get_width() - 1);
                        }
                        this->get_position_row() = new_row;
                        this->get_position_column() = new_column;
                        cout << "(" << new_row << ", " << new_column << ")\n";
                    }
                    else
                    {
                        indexes_to_remove.push_back(i);
                        if (organism->get_name() == "Guarana")
                            this->get_strength() += EAT_GUARANA_STRENGTH_INCERASE;
                    }
                    
                    return;
                }
                else
                {
                    cout << organism->get_name() << " wins the battle with " << this->get_name() << " at (" << row << ", " << column << ")\n";
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
            // Fight with turtle case
            else if (this->get_name() != organism->get_name() && organism->get_name() == "turtle")
            {
                update_previous_move();
                std::cout << "Turtle at (" << row << ", " << column << ") reflects the attack! " << get_name()
                    << " is going back to: (" << get_position_row() << ", " << get_position_column() << ")\n";
            }
            else if (this->get_name() == organism->get_name())
            {
                cout << "Multiplication of " << this->get_name() << " at (" << row << ", " << column << ")\n";
                update_previous_move();
                int counter = 0;
                for (const auto& o : organisms)
                    if (o->get_name() == this->get_name())
                        counter++;
                if (counter > 5)
                    cout << "We cant add more " << this->get_name() << " beacuse we arleady have " << counter << " of them!\n";
                else
                    organisms_to_add.push_back({ this->get_type(), this->get_name(), this->get_position_row(), this->get_position_column()});
            }
        }
    }
}

void Animal::update_previous_move()
{
    if (previous_move == Directions::LEFT) get_position_column()++;
    else if (previous_move == Directions::TOP) get_position_row()++;
    else if (previous_move == Directions::RIGHT) get_position_column()--;
    else if (previous_move == Directions::BOTTOM) get_position_row()--;

    previous_move = Directions::NONE;
}